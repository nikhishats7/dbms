#include "StaticBuffer.h"

// the declarations for this class can be found at "StaticBuffer.h"

unsigned char StaticBuffer::blocks[BUFFER_CAPACITY][BLOCK_SIZE];
struct BufferMetaInfo StaticBuffer::metainfo[BUFFER_CAPACITY];

StaticBuffer::StaticBuffer() {

  // initialise all blocks as free
  for (int bufferIndex=0;bufferIndex<BUFFER_CAPACITY;bufferIndex++/*bufferIndex = 0 to BUFFER_CAPACITY-1*/) {
    metainfo[bufferIndex].free = true;
    metainfo[bufferIndex].dirty = false;
    metainfo[bufferIndex].timeStamp = -1;
    metainfo[bufferIndex].blockNum = -1;
  }
}

/*
At this stage, we are not writing back from the buffer to the disk since we are
not modifying the buffer. So, we will define an empty destructor for now. In
subsequent stages, we will implement the write-back functionality here.
*/
StaticBuffer::~StaticBuffer() {
   for(int i=0;i<BUFFER_CAPACITY;i++)
   {
   	if(metainfo[i].free==false&&metainfo[i].dirty==true)
   	{
   		Disk::writeBlock(StaticBuffer::blocks[i],metainfo[i].blockNum);
   	}
   }
}

int StaticBuffer::getFreeBuffer(int blockNum) {
  if (blockNum < 0 || blockNum > DISK_BLOCKS) {
    return E_OUTOFBOUND;
  }
  
  /*
  int allocatedBuffer;
  for(int index=0;index<BUFFER_CAPACITY;index++)
  {
  	if(metainfo[index].free==true)
  	{
  		allocatedBuffer=index;
  		break;
  	}
  }

  metainfo[allocatedBuffer].free = false;
  metainfo[allocatedBuffer].blockNum = blockNum;

  return allocatedBuffer;
  */
  
  for(int i=0;i<BUFFER_CAPACITY;i++)
  {
  	if(metainfo[i].free==false)
  	metainfo[i].timeStamp++;
  }
  
  int bufferNum=-1;
  for(int i=0;i<BUFFER_CAPACITY;i++)
  {
  	if(metainfo[i].free==true)
  	{
  		bufferNum=i;
  		break;
  	}
  }
  
  if(bufferNum==-1)
  {
  	int timemax=0;
  	for(int i=0;i<BUFFER_CAPACITY;i++)
  	{
  		if(metainfo[i].timeStamp>timemax)
  		{
  			bufferNum=i;
  			timemax=metainfo[i].timeStamp;
  		}
  	}
  	
  	if(metainfo[bufferNum].dirty==true)
  	Disk::writeBlock(StaticBuffer::blocks[bufferNum],metainfo[bufferNum].blockNum);
  }
  
  metainfo[bufferNum].free=false;
  metainfo[bufferNum].dirty=false;
  metainfo[bufferNum].blockNum=blockNum;
  metainfo[bufferNum].timeStamp=0;
  
  return bufferNum;
}


int StaticBuffer::getBufferNum(int blockNum) {
  // Check if blockNum is valid (between zero and DISK_BLOCKS)
  // and return E_OUTOFBOUND if not valid.
	
	if(blockNum<0||blockNum>BUFFER_CAPACITY)
	{
		return E_OUTOFBOUND;
	}
  // find and return the bufferIndex which corresponds to blockNum (check metainfo)
  for(int i=0;i<BUFFER_CAPACITY;i++)
  {
  	if(metainfo[i].free==false&&metainfo[i].blockNum==blockNum)
  	return i;
  }

  // if block is not in the buffer
  return E_BLOCKNOTINBUFFER;
}
int StaticBuffer::setDirtyBit(int blockNum){
    
    int bufferNum=getBufferNum(blockNum);
    if(bufferNum = E_BLOCKNOTINBUFFER)
    return E_BLOCKNOTINBUFFER;
    
    if(bufferNum = E_OUTOFBOUND)
    return E_OUTOFBOUND;
    
    metainfo[bufferNum].dirty=true;
    
    return SUCCESS;
}
























