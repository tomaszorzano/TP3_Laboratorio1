#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#define OK 1
#define ERROR 0


Employee* employee_new()
{
    Employee* emp;
    emp = (Employee*)malloc(sizeof(Employee));
    emp->id = 0;
    strcpy(emp->nombre, "");
    emp->horasTrabajadas = 0;
    emp->sueldo = 0;

    return emp;
};

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr)
{
    Employee* emp;
    emp = (Employee*)malloc(sizeof(Employee));
    emp->id = *idStr;
    strcpy(emp->nombre,nombreStr);
    emp->horasTrabajadas = *horasTrabajadasStr;
    emp->sueldo = 0;

    return emp;
};

void employee_delete()
{

};

int employee_setId(Employee* this,int id)
{
    int ret;
    ret = ERROR;

    if( id > 0 && this != NULL)
    {
        this->id = id;
        ret=OK;
    }

    return ret;
};

int employee_getId(Employee* this,int* id)
{
    int ret;
    ret = ERROR;

    if( this != NULL )
    {
        *id= this->id;
        ret = OK;

    }

    return ret;
};

int employee_setNombre(Employee* this,char* nombre)
{
    int ret;
    ret = ERROR;

    if(this != NULL)
    {
        strcpy(this->nombre, nombre);
        ret=OK;
    }

    return ret;
};
int employee_getNombre(Employee* this,char* nombre)
{
  int ret;
    ret = ERROR;

    if(this != NULL)
    {
        strcpy(nombre,this->nombre);
        ret=OK;
    }

    return ret;
};

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
     int ret;
    ret = ERROR;

    if(this != NULL)
    {
        this->horasTrabajadas= horasTrabajadas;
        ret=OK;
    }

    return ret;
};
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
   int ret;
    ret = ERROR;

    if(this != NULL)
    {
         *horasTrabajadas = this->horasTrabajadas;
        ret=OK;
    }

    return ret;
};
int employee_setSueldo(Employee* this,int sueldo)
{
      int ret;
    ret = ERROR;

    if(this != NULL)
    {
        this->sueldo= sueldo;
        ret=OK;
    }

    return ret;
};

int employee_getSueldo(Employee* this,int* sueldo)
{
    int ret;
    ret = ERROR;

    if(this != NULL)
    {
        *sueldo = this->sueldo;
        ret=OK;
    }

    return ret;
};
void  employee_showEmployee(Employee* this)
{
    if(this != NULL )
    {
        printf ( " %4d  %s  %d  %d \n\n " , this->id , this->nombre , this->horasTrabajadas , this->sueldo);
    }
}

void  employee_showEmployees(Employee* this)
{
    Employee* emp;

    if(this != NULL )
    {
        for(int i=0; i<ll_len(this);i++)
        {
            emp = (Employee*)ll_get(this, i);
            employee_showEmployee(emp);
        }
    }
    else
    {
        printf("No hay empleados cargados\n\n");
        system("pause");
    }

}

int employee_sortByName(void* empleadoA, void* empleadoB)
{
    int ret;
    ret = strcmp(((Employee*)empleadoA)->nombre, ((Employee*)empleadoB)->nombre);
    return ret;
}


int employee_sortById(void* empleadoA, void* empleadoB)
{
    int ret;
    if(((Employee*)empleadoA)->id > ((Employee*)empleadoB)->id)
    {
        ret = 1;
    } if(((Employee*)empleadoA)->id < ((Employee*)empleadoB)->id)
    {
        ret = -1;
    }
    else
    {
        ret = 0;
    }
    return ret;

}

int employee_sortByHsTrabajadas(void* empleadoA, void* empleadoB)
{
    int ret;
    if(((Employee*)empleadoA)->horasTrabajadas > ((Employee*)empleadoB)->horasTrabajadas)
    {
        ret = 1;
    }
    else if(((Employee*)empleadoA)->horasTrabajadas < ((Employee*)empleadoB)->horasTrabajadas)
    {
        ret = -1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}

int employee_sortBySueldo(void* empleadoA, void* empleadoB)
{
    int ret;
    if(((Employee*)empleadoA)->sueldo > ((Employee*)empleadoB)->sueldo)
    {
        ret = 1;
    }
    else if(((Employee*)empleadoA)->sueldo < ((Employee*)empleadoB)->sueldo)
    {
        ret = -1;
    }
    else
    {
        ret = 0;
    }
    return ret;
};




