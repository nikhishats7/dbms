#include "OpenRelTable.h"

#include <cstring>
#include <cstdlib>
#include<string.h>
#include<cstdio>



OpenRelTableMetaInfo OpenRelTable::tableMetaInfo[MAX_OPEN];

OpenRelTable::OpenRelTable() {

  // initialize relCache and attrCache with nullptr
  for (int i = 0; i < MAX_OPEN; ++i) {
    RelCacheTable::relCache[i] = nullptr;
    AttrCacheTable::attrCache[i] = nullptr;
    tableMetaInfo[i].free=1;
  }

  
  RecBuffer relCatBlock(RELCAT_BLOCK);

  Attribute relCatRecord[RELCAT_NO_ATTRS];
  relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_RELCAT);

  struct RelCacheEntry relCacheEntry;
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
  relCacheEntry.recId.block = RELCAT_BLOCK;                                                          //the block and slot in metadata are the locn of relations in relcatalog and that of attributes in 
  relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_RELCAT;							//attrcatalog

  // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[RELCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[RELCAT_RELID]) = relCacheEntry;         //inserting into cache

  




  /**** setting up Attribute Catalog relation in the Relation Cache Table ****/

  relCatBlock.getRecord(relCatRecord, RELCAT_SLOTNUM_FOR_ATTRCAT);

  // struct RelCacheEntry relCacheEntry;
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
  relCacheEntry.recId.block = RELCAT_BLOCK;
  relCacheEntry.recId.slot = RELCAT_SLOTNUM_FOR_ATTRCAT;

  // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[ATTRCAT_RELID] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[ATTRCAT_RELID]) = relCacheEntry;
  
  
  
  //new
  /*
  
  relCatBlock.getRecord(relCatRecord, 2);

  // struct RelCacheEntry relCacheEntry;
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
  relCacheEntry.recId.block = RELCAT_BLOCK;
  relCacheEntry.recId.slot = 2;

  // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[2] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[2]) = relCacheEntry;
  */
  
  //new


  /************ Setting up Attribute cache entries ************/
  
  /**** setting up Relation Catalog relation in the Attribute Cache Table ****/

AttrCacheEntry* listHead=nullptr;
AttrCacheEntry* head;

RecBuffer attrCatBlock(ATTRCAT_BLOCK);         //creating an instance of attrcatlog
Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
for(int i=0;i<=5;i++)
{
 AttrCacheEntry* attrCacheEntry=(struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));

   attrCatBlock.getRecord(attrCatRecord,i); 
  AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry->attrCatEntry);
  attrCacheEntry->recId.block = ATTRCAT_BLOCK;
  attrCacheEntry->recId.slot = i;
  if(listHead==nullptr)
  {
  	listHead=attrCacheEntry;
  	head=listHead;
  }
  else
  {
  	head->next=attrCacheEntry;
  	head=head->next;
  }
}

head->next=nullptr;
AttrCacheTable::attrCache[RELCAT_RELID] = listHead;

 
  /**** setting up Attribute Catalog relation in the Attribute Cache Table ****/


AttrCacheEntry* listHead2;
AttrCacheEntry* head2;

// RecBuffer attrCatBlock(ATTRCAT_BLOCK);
// Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
for(int i=6;i<=11;i++)
{
  AttrCacheEntry* attrCacheEntry=(struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));

   attrCatBlock.getRecord(attrCatRecord,i); 
  AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry->attrCatEntry);
  attrCacheEntry->recId.block = ATTRCAT_BLOCK;
  attrCacheEntry->recId.slot = i;
  if(listHead2==nullptr)
  {
  	listHead2=attrCacheEntry;
  	head2=listHead2;
  }
  else
  {
  	head2->next=attrCacheEntry;
  	head2=head2->next;
  }
}
head2->next=nullptr;

AttrCacheTable::attrCache[ATTRCAT_RELID] = listHead2;


/*
//new


AttrCacheEntry* listHead3=nullptr;
AttrCacheEntry* head3=nullptr;

// RecBuffer attrCatBlock(ATTRCAT_BLOCK);
// Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
for(int i=12;i<=15;i++)
{
  AttrCacheEntry* attrCacheEntry=(struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));

   attrCatBlock.getRecord(attrCatRecord,i); 
  AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry->attrCatEntry);
  attrCacheEntry->recId.block = ATTRCAT_BLOCK;
  attrCacheEntry->recId.slot = i;
  if(listHead3==nullptr)
  {
  	listHead3=attrCacheEntry;
  	head3=listHead3;
  }
  else
  {
  	head3->next=attrCacheEntry;
  	head3=head3->next;
  }
}
head3->next=nullptr;

AttrCacheTable::attrCache[2] = listHead3;

*/

//new


tableMetaInfo[RELCAT_RELID].free=0;
strcpy(tableMetaInfo[RELCAT_RELID].relName,RELCAT_RELNAME);

tableMetaInfo[ATTRCAT_RELID].free=0;
strcpy(tableMetaInfo[ATTRCAT_RELID].relName,ATTRCAT_RELNAME);
}



int OpenRelTable::getRelId(char relName[ATTR_SIZE]) {

  // if relname is RELCAT_RELNAME, return RELCAT_RELID
  // if relname is ATTRCAT_RELNAME, return ATTRCAT_RELID
  /*
  if(strcmp(relName,RELCAT_RELNAME)==0)
  return RELCAT_RELID;

  if(strcmp(relName,ATTRCAT_RELNAME)==0)
  return ATTRCAT_RELID;
  */
  
  for(int i=0;i<MAX_OPEN;i++)
  {
  	if(strcmp(tableMetaInfo[i].relName,relName)==0)
  	return i;
  }
  return E_RELNOTOPEN;
}





OpenRelTable::~OpenRelTable() {

  // close all open relations (from rel-id = 2 onwards. Why?)
  for (int i = 2; i < MAX_OPEN; ++i) {
    if (!tableMetaInfo[i].free) {
      OpenRelTable::closeRel(i); // we will implement this function later
    }
  }

	free(RelCacheTable::relCache[0]);
	free(RelCacheTable::relCache[1]);
  // free the memory allocated for rel-id 0 and 1 in the caches
}


int OpenRelTable::getFreeOpenRelTableEntry() {


//for(int i=0;i<MAX_OPEN;i++)
 //printf("met2=%d ",tableMetaInfo[i].free);
for(int i=0;i<MAX_OPEN;i++)
{
	if(tableMetaInfo[i].free==1)
	{
		//printf("i=%d ",i);
		return i;
	}
}

return E_CACHEFULL;

  /* traverse through the tableMetaInfo array,
    find a free entry in the Open Relation Table.*/

  // if found return the relation id, else return E_CACHEFULL.
}



int OpenRelTable::openRel(char relName[ATTR_SIZE]) {

int k=OpenRelTable::getRelId(relName);
  if(k!= E_RELNOTOPEN/* the relation `relName` already has an entry in the Open Relation Table */){
    // (checked using OpenRelTable::getRelId())

    // return that relation id;
    return k;
  }
  
  

 //for(int i=0;i<MAX_OPEN;i++)
 //printf("met=%d ",tableMetaInfo[i].free);

int f=OpenRelTable::getFreeOpenRelTableEntry();
  if (f==E_CACHEFULL/* free slot not available */){
    return E_CACHEFULL;
  }

  // let relId be used to store the free slot.
  int relId=f;

  /****** Setting up Relation Cache entry for the relation ******/

	RelCacheTable::resetSearchIndex(RELCAT_RELID);
  /* search for the entry with relation name, relName, in the Relation Catalog using
      BlockAccess::linearSearch().
      Care should be taken to reset the searchIndex of the relation RELCAT_RELID
      before calling linearSearch().*/

  // relcatRecId stores the rec-id of the relation `relName` in the Relation Catalog.
 
  /*** Convert strVal (string) to an attribute of data type NUMBER or STRING ***/
 // int type = attrCatEntry.attrType;
  Attribute relationName;
  
  strcpy(relationName.sVal, relName);
  
  char attrname[16]="RelName";
  RecId relcatRecId= BlockAccess::linearSearch(RELCAT_RELID,attrname, relationName,EQ);

  if (relcatRecId.block==-1&&relcatRecId.slot==-1) {
    // (the relation is not found in the Relation Catalog.)
    return E_RELNOTEXIST;
  }


RecBuffer relcatblo(relcatRecId.block);
Attribute relCatRecord[6];
relcatblo.getRecord(relCatRecord,relcatRecId.slot);

  struct RelCacheEntry relCacheEntry;
  RelCacheTable::recordToRelCatEntry(relCatRecord, &relCacheEntry.relCatEntry);
  relCacheEntry.recId.block =  relcatRecId.block; //relcat block                                                        //the block and slot in metadata are the locn of relations in relcatalog and that of attributes in 
  relCacheEntry.recId.slot = relcatRecId.slot;							//attrcatalog

  // allocate this on the heap because we want it to persist outside this function
  RelCacheTable::relCache[relId] = (struct RelCacheEntry*)malloc(sizeof(RelCacheEntry));
  *(RelCacheTable::relCache[relId]) = relCacheEntry;         //inserting into cache

  
  /* read the record entry corresponding to relcatRecId and create a relCacheEntry
      on it using RecBuffer::getRecord() and RelCacheTable::recordToRelCatEntry().
      update the recId field of this Relation Cache entry to relcatRecId.
      use the Relation Cache entry to set the relId-th entry of the RelCacheTable.
    NOTE: make sure to allocate memory for the RelCacheEntry using malloc()
  */

  /****** Setting up Attribute Cache entry for the relation ******/

  // let listHead be used to hold the head of the linked list of attrCache entries.
  AttrCacheEntry* listHead=nullptr;
  AttrCacheEntry* head=nullptr;
  
  RelCacheTable::resetSearchIndex(ATTRCAT_RELID);
  //RecBuffer attrCatBlock(ATTRCAT_BLOCK);         //creating an instance of attrcatlog
Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
  
  
  //printf("add=%d ",relId);
  
  
  //int count=0;
  while (true) {
    RecId attrcatRecId = BlockAccess::linearSearch(ATTRCAT_RELID,attrname, relationName,EQ);

    if (attrcatRecId.block != -1 && attrcatRecId.slot != -1) 
    {

RecBuffer attrCatBlock(attrcatRecId.block);
 AttrCacheEntry* attrCacheEntry=(struct AttrCacheEntry*)malloc(sizeof(AttrCacheEntry));

	//printf("block=%d slot=%d ",attrcatRecId.block,attrcatRecId.slot);
   attrCatBlock.getRecord(attrCatRecord,attrcatRecId.slot); 
  AttrCacheTable::recordToAttrCatEntry(attrCatRecord, &attrCacheEntry->attrCatEntry);
  //printf("attrnaam=%s ",attrCacheEntry->attrCatEntry.attrName);
  attrCacheEntry->recId.block = attrcatRecId.block;
  attrCacheEntry->recId.slot = attrcatRecId.slot;
	  if(listHead==nullptr)
	  {
	  	listHead=attrCacheEntry;
	  	head=listHead;
	  }
	  else
	  {
	  	head->next=attrCacheEntry;
	  	head=head->next;
	  }

	//count++;
	//printf("count=%d ",count);

    } 
    else {
      // (all records over)
      break;
    }
  }
  
  
  
  head->next=nullptr;
AttrCacheTable::attrCache[relId] = listHead;
  
  tableMetaInfo[relId].free=0;
  strcpy(tableMetaInfo[relId].relName,relName);

  return relId;
}




int OpenRelTable::closeRel(int relId) {
  if (relId==0||relId==1/* rel-id corresponds to relation catalog or attribute catalog*/) {
    return E_NOTPERMITTED;
  }

  if (relId<0||relId>=MAX_OPEN/* 0 <= relId < MAX_OPEN */) {
    return E_OUTOFBOUND;
  }

  if (tableMetaInfo[relId].free==true/* rel-id corresponds to a free slot*/) {
    return E_RELNOTOPEN;
  }

  // free the memory allocated in the relation and attribute caches which was
  // allocated in the OpenRelTable::openRel() function
 // free(RelCacheTable::relCache[relId]);
 // free(AttrCacheTable::attrCache[relId]);

  tableMetaInfo[relId].free=1;
  free(RelCacheTable::relCache[relId]);
  RelCacheTable::relCache[relId]=nullptr;
  AttrCacheTable::attrCache[relId]=nullptr;
  // update `tableMetaInfo` to set `relId` as a free slot
  // update `relCache` and `attrCache` to set the entry at `relId` to nullptr

  return SUCCESS;
}

/*
OpenRelTable::~OpenRelTable() {
  // free all the memory that you allocated in the constructor
  //OpenRelTableMetaInfo tableMetaInfo[RELCAT_RELID]->free=false;
  //tableMetaInfo[RELCAT_RELID].relName=RELCAT_RELNAME;

 // OpenRelTableMetaInfo tableMetaInfo[ATTRCAT_RELID]->free=false;
  //tableMetaInfo[ATTRCAT_RELID].relName='ATTRIBUTECAT';
}
*/

