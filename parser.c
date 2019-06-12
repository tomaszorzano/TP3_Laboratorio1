#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

#define OK 1
#define ERROR 0

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{

    int ret;
    ret = ERROR;
    int cant = 0;
    char idStr[6];
    char nombreStr[20];
    char horasTrabajadasStr[6];
    char sueldoStr[6];

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            cant = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,\n]\n", idStr, nombreStr, horasTrabajadasStr, sueldoStr);
            if(cant != 4)
            {
                printf("Error al cargar Arvhivo\n\n");
                system("pause");
            }
            else
            {
                Employee* emp = employee_new();
                emp->id = atoi(idStr);
                strcpy(emp->nombre, nombreStr);
                emp->horasTrabajadas = atoi(horasTrabajadasStr);
                emp->sueldo = atoi(sueldoStr);
                ll_add(pArrayListEmployee, emp);
            }
        }
    fclose(pFile);
    ret=OK;
    }
    else
    {
        printf("Arvhivo hay datos\n\n");
        system("pause");
    }

    return ret;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
  int ret;
    ret = ERROR;

    if(pFile != NULL)
    {
        while(!feof(pFile))
        {

                Employee* emp = employee_new();
                ret = fread(emp, sizeof(Employee),1,pFile);
                if(ret != 1)
                {
                    printf("Error al caargar datos\n");
                }
                else
                {
                    ll_add(pArrayListEmployee, emp);
                }
        }
    fclose(pFile);
    ret = OK;
    }
    else
    {
        printf("No hay datos");
        system("pause");
    }

    return ret;
}
