#include "BlockAccess.h"

#include <cstring>
#include<iostream>
using namespace std;

RecId BlockAccess::linearSearch(int relId, char attrName[ATTR_SIZE], union Attribute attrVal, int op) {
    // get the previous search index of the relation relId from the relation cache
    // (use RelCacheTable::getSearchIndex() function)
    RecId prevRecId;
    RelCacheTable::getSearchIndex(relId,&prevRecId);

    // let block and slot denote the record id of the record being currently checked
    int block;int slot;


    // if the current search index record is invalid(i.e. both block and slot = -1)
    if (prevRecId.block == -1 && prevRecId.slot == -1)
    {
        // (no hits from previous search; search should start from the
        // first record itself)

        // get the first record block of the relation from the relation cache
        // (use RelCacheTable::getRelCatEntry() function of Cache Layer)
        struct RelCatEntry relCatBuf;
        RelCacheTable::getRelCatEntry(relId,&relCatBuf);

        // block = first record block of the relation
        // slot = 0
        block=relCatBuf.firstBlk;
          slot=0;
    }
    else
    {
        // (there is a hit from previous search; search should start from
        // the record next to the search index record)
	
        // block = search index's block
        // slot = search index's slot + 1
        block=prevRecId.block;
        slot=prevRecId.slot+1;
    }

    /* The following code searches for the next record in the relation
       that satisfies the given condition
       We start from the record id (block, slot) and iterate over the remaining
       records of the relation
       */
       
    while (block != -1)
    {
        /* create a RecBuffer object for block (use RecBuffer Constructor for
           existing block) */
           RecBuffer relBuffer(block);

        // get the record with id (block, slot) using RecBuffer::getRecord()
        // get header of the block using RecBuffer::getHeader() function
        // get slot map of the block using RecBuffer::getSlotMap() function
       
       Attribute Record[6];
       relBuffer.getRecord(Record,slot);
       
       HeadInfo head;
       relBuffer.getHeader(&head);
	unsigned char slotMap[head.numSlots];
    relBuffer.getSlotMap(slotMap);
	
	
    //     // If slot >= the number of slots per block(i.e. no more slots in this block)
       if(slot>=head.numSlots)
        {
    //         // update block = right block of block
    //         // update slot = 0
             block=head.rblock;
             slot=0;
             continue;  // continue to the beginning of this while loop
         }

    //     // if slot is free skip the loop
    //     // (i.e. check if slot'th entry in slot map of block contains SLOT_UNOCCUPIED)
        if(slotMap[slot]==SLOT_UNOCCUPIED)
         {
        //     // increment slot and continue to the next record slot
             slot++;
        //     //break;
             continue;
         }

        // // compare record's attribute value to the the given attrVal as below:
        // /*
        //     firstly get the attribute offset for the attrName attribute
        //     from the attribute cache entry of the relation using
        //     AttrCacheTable::getAttrCatEntry()
        
        //AttrCacheEntry attrCacheEntry;
        struct AttrCatEntry attrCatEntry;
         AttrCacheTable::getAttrCatEntry(relId,attrName,&attrCatEntry);
         int offset=attrCatEntry.offset;
         //printf("%d ",offset);
        // /* use the attribute offset to get the value of the attribute from
        //    current record */
  
  
	Attribute attr1=Record[offset];
	
	int cmpVal;  // will store the difference between the attributes
	// // set cmpVal using compareAttrs()
        cmpVal=compareAttrs(attr1,attrVal,attrCatEntry.attrType);

    //     /* Next task is to check whether this record satisfies the given condition.
    //        It is determined based on the output of previous comparison and
    //        the op value received.
    //        The following code sets the cond variable if the condition is satisfied.
    //     */
        
        if (
             (op == NE && cmpVal != 0) ||    // if op is "not equal to"
             (op == LT && cmpVal < 0) ||     // if op is "less than"
             (op == LE && cmpVal <= 0) ||    // if op is "less than or equal to"
             (op == EQ && cmpVal == 0) ||    // if op is "equal to"
             (op == GT && cmpVal > 0) ||     // if op is "greater than"
             (op == GE && cmpVal >= 0)       // if op is "greater than or equal to"
         ) {
        //     /*
        //     set the search index in the relation cache as
        //     the record id of the record that satisfies the given condition
        //     (use RelCacheTable::setSearchIndex function)
        //     */
            
            
             RecId ind={block,slot};
	     RelCacheTable::setSearchIndex(relId,&ind);
	     return ind;
         }

         slot++;
    //block=-1;
        
    }
    
    //while end

    // no record in the relation with Id relid satisfies the given condition
    return RecId{-1, -1};
}









int BlockAccess::renameRelation(char oldName[ATTR_SIZE], char newName[ATTR_SIZE]){
    
    RelCacheTable::resetSearchIndex(RELCAT_RELID);
    
    Attribute newRelationName;
    strcpy(newRelationName.sVal, newName);
     
     
    RecId found=BlockAccess::linearSearch(RELCAT_RELID,RELCAT_ATTR_RELNAME,newRelationName,EQ);
    
    if(found.block!=-1&&found.slot!=-1)
    return E_RELEXIST;
    
    RelCacheTable::resetSearchIndex(RELCAT_RELID);
    
    Attribute oldRelationName;
    strcpy(oldRelationName.sVal, oldName);
    
    found=BlockAccess::linearSearch(RELCAT_RELID,RELCAT_ATTR_RELNAME,oldRelationName,EQ);
    if(found.block==-1&&found.slot==-1)
    return E_RELNOTEXIST;
    
    RecBuffer relCatBlock(RELCAT_BLOCK);
    Attribute relCatRecord[RELCAT_NO_ATTRS];
    relCatBlock.getRecord(relCatRecord,found.slot);
    
    relCatRecord[RELCAT_REL_NAME_INDEX]=newRelationName;
    relCatBlock.setRecord(relCatRecord,found.slot);
    
    
    RelCacheTable::resetSearchIndex(ATTRCAT_RELID);
    int numattr=relCatRecord[RELCAT_NO_ATTRIBUTES_INDEX].nVal;
    
    for(int i=0;i<numattr;i++)
    {
    	found=BlockAccess::linearSearch(ATTRCAT_RELID,ATTRCAT_ATTR_RELNAME,oldRelationName,EQ);
    	
    	RecBuffer attrCatBlock(found.block);
    	Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
        attrCatBlock.getRecord(attrCatRecord,found.slot);
    
        attrCatRecord[ATTRCAT_REL_NAME_INDEX]=newRelationName;
        attrCatBlock.setRecord(attrCatRecord,found.slot);
    	
    }
    
    return SUCCESS;
}



int BlockAccess::renameAttribute(char relName[ATTR_SIZE], char oldName[ATTR_SIZE], char newName[ATTR_SIZE]) {

    RelCacheTable::resetSearchIndex(RELCAT_RELID);

    Attribute relNameAttr;
    strcpy(relNameAttr.sVal,relName);
    
    RecId found=BlockAccess::linearSearch(RELCAT_RELID,RELCAT_ATTR_RELNAME,relNameAttr,EQ);
    if(found.block==-1&&found.slot==-1)
    return E_RELNOTEXIST;
    
    RelCacheTable::resetSearchIndex(ATTRCAT_RELID);
    
    RecId attrToRenameRecId{-1, -1};
    Attribute attrCatEntryRecord[ATTRCAT_NO_ATTRS];
    
    while(true)
    {
    	found=BlockAccess::linearSearch(ATTRCAT_RELID,ATTRCAT_ATTR_RELNAME,relNameAttr,EQ);
    	
    	if(found.block==-1&&found.slot==-1)
    	break;
    	
    	RecBuffer attrcatblock(found.block);
    	attrcatblock.getRecord(attrCatEntryRecord,found.slot);
    	
    	if(strcmp(attrCatEntryRecord[ATTRCAT_ATTR_NAME_INDEX].sVal,oldName)==0)
    	{
    		attrToRenameRecId.block=found.block;
    		attrToRenameRecId.slot=found.slot;
    	}
    	
    	if(strcmp(attrCatEntryRecord[ATTRCAT_ATTR_NAME_INDEX].sVal,newName)==0)
    	return E_ATTREXIST;
    	
    }
    
    if(attrToRenameRecId.block==-1&&attrToRenameRecId.slot==-1)
    return E_ATTRNOTEXIST;
    
    RecBuffer attrcatblock(attrToRenameRecId.block);
    attrcatblock.getRecord(attrCatEntryRecord,attrToRenameRecId.slot);
    Attribute newNameattr;
    strcpy(newNameattr.sVal,newName);
    attrCatEntryRecord[ATTRCAT_ATTR_NAME_INDEX]=newNameattr;
    attrcatblock.setRecord(attrCatEntryRecord,attrToRenameRecId.slot);
    return SUCCESS;
}
























