#include "Cache/OpenRelTable.h"
#include "Disk_Class/Disk.h"
#include "Buffer/StaticBuffer.h"
#include "FrontendInterface/FrontendInterface.h"

#include<iostream>
#include<cstring>
#include<string.h>
using namespace std;


int main(int argc, char *argv[]) {
  Disk disk_run;
  StaticBuffer buffer;
  OpenRelTable cache;

  return FrontendInterface::handleFrontend(argc, argv);
}


//main

/*
int main(int argc, char *argv[]) {

	
  Disk disk_run;
  StaticBuffer buffer;           //creating buffer
  RecBuffer relCatBuffer(RELCAT_BLOCK);
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);
  
   HeadInfo relCatHeader;
   HeadInfo attrCatHeader;
  
  relCatBuffer.getHeader(&relCatHeader);
  attrCatBuffer.getHeader(&attrCatHeader);
  
  std::cout<<relCatHeader.numEntries;
  std::cout<<attrCatHeader.numEntries;
  
  
  for (int i=0;i<relCatHeader.numEntries;i++) {

    Attribute relCatRecord[RELCAT_NO_ATTRS]; // will store the record from the relation catalog

    relCatBuffer.getRecord(relCatRecord, i);

    printf("Relation: %s\n", relCatRecord[RELCAT_REL_NAME_INDEX].sVal);

    for (int j=0;j<attrCatHeader.numEntries;j++) {

      // declare attrCatRecord and load the attribute catalog entry into it
      Attribute attrCatRecord[ATTRCAT_NO_ATTRS];
      attrCatBuffer.getRecord(attrCatRecord,j);

      if (strcmp(relCatRecord[RELCAT_REL_NAME_INDEX].sVal,attrCatRecord[ATTRCAT_REL_NAME_INDEX].sVal)==0) {
        const char *attrType = attrCatRecord[ATTRCAT_ATTR_TYPE_INDEX].nVal == NUMBER ? "NUM" : "STR";
        printf("  %s: %s\n", attrCatRecord[ATTRCAT_ATTR_NAME_INDEX].sVal, attrType);
      }
    }
    printf("\n");
  }
  
}

*/













//BlockBuffer





/*
int main(int argc, char *argv[]) {

	
  Disk disk_run;
  StaticBuffer buffer;           //creating buffer
  OpenRelTable cache;
  
  //new
  RecBuffer attrCatBuffer(ATTRCAT_BLOCK);
  HeadInfo attrCatHeader;
  attrCatBuffer.getHeader(&attrCatHeader);
  
  //std::cout<<relCatHeader.numEntries;
  std::cout<<attrCatHeader.numEntries;
  std::cout<<attrCatHeader.numSlots;
  //new
  
  struct RelCatEntry relCatEntry;
  //struct AttrCacheEntry attrCacheEntry;
  for(int i=0;i<=2;i++)
  {
  	RelCacheTable::getRelCatEntry(i,&relCatEntry);
  	printf("Relation: %s\n", relCatEntry.relName);
  	
  	int num_attr=relCatEntry.numAttrs;
  	cout<<num_attr;
  	cout<<relCatEntry.firstBlk;
  	
  	struct AttrCatEntry attrCatEntry;
  	for(int j=0;j<num_attr;j++)
  	{
  		AttrCacheTable::getAttrCatEntry(i,j,&attrCatEntry);
		//AttrCacheTable::getAttrCatEntry(i,j,&attrCacheEntry.attrCatEntry);
		const char *attrtype=attrCatEntry.attrType==NUMBER?"NUM":"STR";
		printf("  %s: %s\n", attrCatEntry.attrName,attrtype);
  		//printf("  %s\n",attrtype);
  	}
  	
  	
  }
  
}
*/


