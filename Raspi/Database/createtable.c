#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv,char **azColName){
  int i;

  for(i=0;i<argc;i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char *argv[]){
  sqlite3 *db;
  char *zErrMsg=0;
  int rc;
  char *sql;

  //Abrir base datos
  rc=sqlite3_open("water.db",&db);
  if(rc){
    fprintf(stderr, "No se puede abrir la base de datos: %s\n",sqlite3_errmsg(db));
    exit(0);
  }
  else{
    fprintf(stdout,"Base de datos abierta correctamente\n");
  }

  /*Crear base de datos*/
  sql= "CREATE TABLE WATERTB("\
       "ID INT PRIMARY KEY         NOT NULL,"\
       "TIME           TIMESTAMP   NOT NULL,"\
       "PRESSURE       REAL        NOT NULL,"\
       "TEMPERATURE    REAL        NOT NULL,"\
       "POSX           INT         NOT NULL,"\
       "POSY           INT         NOT NULL);";

  /*Ejectutar SQL*/
  rc=sqlite3_exec(db,sql,callback,0,&zErrMsg);
  if(rc!=SQLITE_OK){
    fprintf(stderr,"SQL error: %s\n",zErrMsg);
      sqlite3_free(zErrMsg);
  }else{
    fprintf(stdout,"Tabla creada correctamente");
  }
  sqlite3_close(db);
  return 0;
}
