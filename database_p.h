#ifndef REPREPRO_DATABASE_P_H
#define REPREPRO_DATABASE_P_H

#ifndef REPREPRO_DATABASE_H
#include "database.h"
#endif

#include <db.h>

struct references;
struct filesdb;

struct database {
	char *directory;
	struct filesdb *files;
	struct references *references;
	bool locked;
};

retvalue database_opentable(struct database *,const char *,const char *,DBTYPE,u_int32_t flags,u_int32_t preflags,int (*)(DB *,const DBT *,const DBT *),/*@out@*/DB **);
retvalue database_listsubtables(struct database *,const char *,/*@out@*/struct strlist *);

#define CLEARDBT(dbt) {memset(&dbt,0,sizeof(dbt));}
#define SETDBT(dbt,datastr) {const char *my = datastr;memset(&dbt,0,sizeof(dbt));dbt.data=(void *)my;dbt.size=strlen(my)+1;}

#endif