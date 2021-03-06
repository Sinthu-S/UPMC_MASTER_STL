/**
 * @file bio.c
 * @author Karagiannis Antonios
 */
#include <stdio.h>

#include <buf.h>
#include <callo.h>
#include <synch.h>
#include <var.h>
#include <conf.h>

#define PRIBIO 100
#define NODEV  19

/**
 * @fn void notavail(struct buf *bp)
#include <callo.h> 
#include <sched.h> 

* Retire un buffer de la liste des buffers disponible et le marque � BUSY.
 * 
 * Unlink a buffer from the available list and mark it busy.
 * (internal interface)
 * @param bp : pointeur vers un buffer
 */
void notavail(struct buf *bp) {
  int s;
  s=splbio ();
  bp->av_back->av_forw = bp->av_forw;
  bp->av_forw->av_back = bp->av_back;
  bp->b_flags |= B_BUSY;
  spl(s);
}

/**
 * @fn void iowait(struct buf *bp)
 * Attend la fin d'un E/S sur le buffer et rend les erreurs �ventuelles.
 *
 * Wait for I/O completion on the buffer; return errors
 * to the user.
 * @param bp : pointeur vers un buffer
 */
void iowait(struct buf *bp) {
  
  while ((bp->b_flags&B_DONE)==0) {
    tsleep(PRIBIO, (caddr_t)bp);
  }
}

/**
 * @fn void iodone(struct buf *bp)
 * Permet de signaler la fin d'une E/S sur un buffer et reveille les processus endormis
 * sur le buffer (� condition qu'il en existe).
 *
 * Mark I/O complete on a buffer, release it if I/O is asynchronous,
 * and wake up anyone waiting for it.
 * @param bp : pointeur vers un buffer
 */
void iodone(struct buf *bp) {
  
  /*  if(bp->b_flags&B_MAP) */
  /*     mapfree(bp); */
  bp->b_flags |= B_DONE;
  if (bp->b_flags&B_ASYNC)
    brelse(bp);
  else {
    bp->b_flags &= ~B_WANTED;
    twakeup((caddr_t)bp);
  }
}

/**
 * @fn void incore(int dev, bc_daddr_t blkno)
 * Test si le bloc demand� est associ� � un buffer
 *
 * See if the block is associated with some buffer
 * (mainly to avoid getting hung up on a wait in breada)
 * @param dev : device (major+minor)
 * @param blkno : num�ro de bloc
 * @return 1 si le bloc est associ� � un buffer, sinon 0
 */
int incore(int dev, bc_daddr_t blkno) {
  struct buf *bp;
  struct buf *dp;
  
  dp = bhash(dev, blkno); 
  for (bp=dp->b_forw; bp != dp; bp = bp->b_forw)
    if (bp->b_blkno==blkno && bp->b_dev==dev)
      return(1);
  return(0);
}

/**
 * @fn void brelse(struct buf *bp)
 * Libere le buffer sans g�n�rer de E/S.
 *
 * Release the buffer, with no I/O implied.
 * @param bp : pointeur vers un buffer
 */
void brelse(struct buf *bp) {
  struct buf **backp;
  int flags; int s;

  MASK_ALRM;

  bp->flags &=~ B_BUSY;
  if(bp->flag & B_WANTED){
    bp->flag &=~ B_WANTED;
    twakeup((caddr_t)bp);
  }

  bp->av_back = bfreelist.av_back;
  bp->av_forw = &bfreelist;
  bfreelist.av_back= bp;
  bp->av_back->av_forw = bp;
  bfreelist.b_bcount++;
  if(bfreelist.flags&B_WANTED){
     bfreelist->flag &=~ B_WANTED;
    twakeup((caddr_t)bfreelist);
}

/**
 * @fn struct buf *bread(int dev, bc_daddr_t blkno)
 * Permet la lecture d'un bloc physique (si n�c�saire) et rend 
 * le buffer lu
 *
 * Read in (if necessary) the block and return a buffer pointer
 * @param dev : device (major+minor)
 * @param blkno : num�ro de bloc
 * @return le buffer associ� au device dev et de num�ro de bloc blkno
 */
struct buf *bread(int dev, bc_daddr_t blkno) {
  struct buf *bp;
  return bp;
}

/**
 * @fn struct buf *breada(int dev, bc_daddr_t blkno, bc_daddr_t rablkno)
 * Lit le bloc demand� et lance une e/s sur le bloc suivant du device
 *
 * Read in the block, like bread, but also start I/O on the
 * read-ahead block (which is not allocated to the caller)
 * @param dev : device (major+minor)
 * @param blkno : num�ro de bloc
 * @param rablkno : read-ahead bloc
 * @return le buffer associ� au device dev et de num�ro de bloc blkno
 */
struct buf *breada(int dev, bc_daddr_t blkno, bc_daddr_t rablkno) {
  struct buf *bp, *rabp;
  
  bp = NULL;
  if (!incore(dev, blkno)) {
    bp = getblk(dev, blkno);
    if ((bp->b_flags&B_DONE) == 0) {
      bp->b_flags |= B_READ;
      bp->b_count = BSIZE;
      (*bdevsw[major(dev)].d_strategy)(bp);
    }
  }
  if (rablkno && !incore(dev, rablkno)) {
    rabp = getblk(dev, rablkno);
    if (rabp->b_flags & B_DONE)
      brelse(rabp);
    else {
      rabp->b_flags |= B_READ|B_ASYNC;
      rabp->b_count = BSIZE;
      (*bdevsw[major(dev)].d_strategy)(rabp);
    }
  }
  if(bp == NULL)
    return(bread(dev, blkno));
  iowait(bp);
  return(bp);
}

/**
 * @fn void bwrite(struct buf *bp)
 * Permet l'ecrire sur disque du buffer et la lib�ration de celui-ci si l'ecriture est synchrone
 *
 * Write the buffer, waiting for completion.
 * Then release the buffer.
 * @param bp : pointeur vers un buffer
 */
void bwrite(struct buf *bp) {
  int flag;

}

/**
 * @fn void bdwrite(struct buf *bp)
 * Marque le buffer � sale et le lib�re
 * 
 * Release the buffer, marking it so that if it is grabbed
 * for another purpose it will be written out before being
 * given up (e.g. when writing a partial block where it is
 * assumed that another write for the same block will soon follow).
 * This can't be done for magtape, since writes must be done
 * in the same order as requested.
 * @param bp : pointeur vers un buffer
 */
void bdwrite(struct buf *bp) {
  bp->b_flags |= B_DELWRI | B_DONE;
  bp->b_resid = 0;
  brelse(bp);
}

/**
 * @fn void bawrite(struct buf *bp)
 * Lib�re le buffer et effectue l'�criture en asynchrone
 *
 * Release the buffer, start I/O on it, but don't wait for completion.
 * @param bp : pointeur vers un buffer
 */
void bawrite(struct buf *bp) {
  bp->b_flags |= B_ASYNC;
  bwrite(bp);
}

/**
 * @fn struct buf *getblk(int dev, bc_daddr_t blkno)
 * Permet de r�cuperer un buffer en fonction d'un device et d'un num�ro de bloc.
 * S'il n'existe pas dans la table de hachage des buffers pr�c�demment allou�s, un buffer est
 * retir� de la liste des buffers disponibles et allou� au device et au bloc correspondant
 * 
 * Assign a buffer for the given block. If the appropriate
 * block is already associated, return it; otherwise search
 * for the oldest non-busy buffer and reassign it.
 * @param dev : device (major+minor)
 * @param blkno : num�ro de bloc
 * @return le buffer associ� au device dev et de num�ro de bloc blkno
 */
struct buf *getblk(int dev, bc_daddr_t blkno) {
  
  struct buf *bp;
  struct buf *dp;

 loop:
  UNMASK_ALRM;
  dp = bhash(dev, blkno); 
  if(dp == NULL)
    printf("devtab");
  for(bp=dp->b_forw; bp != dp; bp=bp->b_forw){
    if(bp->b_blkno != blkno || bp->b_dev != dev)
      continue;
    MASK_ALRM;
    if(bp->b_flags&B_BUSY){
      bp->b_flags |= B_WANTED;
      tsleep(PRIBIO+1, (caddr_t)bp);
      goto loop;
    }
    UNMASK_ALRM;
    notavail(bp);
    return bp;
  }
  MASK_ALRM;
  if(bfreelist.av_forw == &bfreelist){
    bfreelist.b_flags |= B_WANTED;
    tsleep(PRIOBIO+1, (caddr_t)&bfreelist);
    goto loop;
  }
  UNMASK_ALRM;
  bp=bfreelist.av_forw;
  notavail(bp);
  if(bp->b_flags & B_DELWRI){
    bp->b_flags |= B_ASYNC;
    bwrite(bp);
    goto loop;
  }
  
  bp->b_flag = B_BUSY;
  bp->b_bac->b_forw = bp->b_forw ;
  bp->b_forw->b_back = bp->b_back ;
  bp->b_forw = dp->b_forw ;
  bp->b_back = dp ;
  dp->b_forw->b_back = bp ;
  dp->b_forw = bp ;
  bp->b_dev = dev ;
  bp->b_blkno = blkno ;

  return bp;
  
}
