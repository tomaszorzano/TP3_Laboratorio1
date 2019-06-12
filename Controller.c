#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "Controller.h"
#include "parser.h"

#define OK 1
#define ERROR 0


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
   int ret;
    ret = ERROR;

    FILE* pFile = fopen("data.csv", "r");
    if(pFile != NULL)
    {
        ret = parser_EmployeeFromText(pFile, pArrayListEmployee);
    }
    else
    {
        printf("El Archivo No Existe\n\n");
        system("pause");
    }

    return ret;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
     int ret;
    ret =  ERROR;

    FILE* pFile = fopen("data.bin", "rb");
    if(pFile != NULL)
    {
        ret = parser_EmployeeFromBinary(pFile, pArrayListEmployee);
    }
    else
    {
        printf("El Archivo No Existe\n\n");
        system("pause");
    }

    return ret;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
     int ret;
    ret = ERROR;

    Employee* emp = employee_new();
    int id;
    char nombre[20];
    int horasTeabajadas;
    int sueldo;

    if(pArrayListEmployee != NULL)
    {
        printf("Ingrese ID: ");
        scanf("%d", &id);
        ret = employee_setId(emp, id);

        printf("Ingrese Nombre: ");
        scanf("%s", nombre);
        ret = employee_setNombre(emp, nombre);

        printf("Ingrese Horas Trabajadas: ");
        scanf("%d", &horasTeabajadas);
        ret = employee_setHorasTrabajadas(emp, horasTeabajadas);

        printf("Ingrese Sueldo: ");
        scanf("%d", &sueldo);
        ret = employee_setSueldo(emp, sueldo);

        ret = ll_add(pArrayListEmployee, emp);
    }
    else
    {
        printf("No hay Datos\n\n");
    }
    return ret;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int respuesta =ERROR;
    int idEmployee = 0;
    int idEmployeeEdit = 0;
    void* aux = employee_new();
    char name[20];
    int horasTrabajadas = 0;
    int sueldo = 0;

    if(pArrayListEmployee != NULL)
    {
        printf("Ingrese un ID\n");
        scanf("%d", &idEmployeeEdit);

        for(int i = 0; i < ll_len(pArrayListEmployee); i++)
        {
            aux = ll_get(pArrayListEmployee, i);

            respuesta = employee_getId((Employee*) aux, &idEmployee);

            if(respuesta == OK)
            {
                if(idEmployee == idEmployeeEdit)
                {
                    switch(menuEdit())
                    {
                    case 1:

                        printf("Ingrese un nombre.\n");
                        scanf("%s", name);
                        respuesta = employee_setNombre((Employee*)aux, name);
                        break;
                    case 2:

                        do
                        {
                            printf("Ingrese Horas Trabajadas\n");
                            scanf("%d", &horasTrabajadas);
                            respuesta = employee_setHorasTrabajadas((Employee*) aux, horasTrabajadas);
                        }
                        while(horasTrabajadas < 0);
                        break;
                    case 3:

                        do
                        {
                            printf("Ingrese Sueldo\n");
                            scanf("%d", &sueldo);
                            respuesta = employee_setSueldo((Employee*) aux, sueldo);
                        }
                        while(sueldo < 0);
                        break;
                    default:
                        break;
                    }

                    if(respuesta == ERROR)
                    {
                        printf("\nProblemas pata modificar el campo.\n");
                    }

                    respuesta = ll_set(pArrayListEmployee, i, aux);
                    break;
                }
            }
        }
    }
    else
    {
        printf("No hay datos en la lista.\n");
    }

    return 1;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
   int respuesta = ERROR;
    int idEmployee;
    int idEmployeeRemove;
    Employee* aux = employee_new();

    if(pArrayListEmployee != NULL)
    {
        printf("Ingrese un ID\n");
        scanf("%d", &idEmployeeRemove);

        for(int i = 0; i < ll_len(pArrayListEmployee); i++)
        {
            aux = (Employee*) ll_get(pArrayListEmployee, i);

            respuesta = employee_getId(aux, &idEmployee);

            if(respuesta == OK)
            {
                if(idEmployee == idEmployeeRemove)
                {
                    respuesta = ll_remove(pArrayListEmployee, i);
                    break;

                }
            }
        }
    }
    else
    {
        printf("No hay datos en la lista.\n");
    }

    return respuesta;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int ret;
    ret = ERROR;
    int len;
    len = ll_len(pArrayListEmployee);

    if(pArrayListEmployee != NULL)
    {
        if(len != 0)
        {
            printf("Id  Nombre  Hs.Trab.  Sueldo\n\n");
            for(int i = 0; i < len; i++)
            {
                employee_showEmployees(pArrayListEmployee);

                ret = OK;
                break;
            }
            system("pause");
        }
        else
        {
            printf("No hay datos\n\n");
            system("pause");
        }
    }
    return ret;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int ret;
    ret =ERROR;
    if(pArrayListEmployee != NULL)
    {
        switch(menuSort())
        {
        case 1:
                ll_sort(pArrayListEmployee, employee_sortById,1);
                employee_showEmployees(pArrayListEmployee);
                break;
        case 2:
                ll_sort(pArrayListEmployee, employee_sortByName,1);
                employee_showEmployees(pArrayListEmployee);
                break;
        case 3:
                ll_sort(pArrayListEmployee, employee_sortByHsTrabajadas,1);
                employee_showEmployees(pArrayListEmployee);
                break;
        case 4:
                ll_sort(pArrayListEmployee, employee_sortBySueldo,1);
                employee_showEmployees(pArrayListEmployee);
                break;
        case 5:
                break;
        }
    }
    else
    {
        printf("No hay datos\n");
    }
    system("pause");

    return ret;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
     int respuesta = ERROR;
    int longitud;

    if(ll_len(pArrayListEmployee) == 0)
    {
        printf("No hay datos en la lista.\n");
    }
    else
    {
        FILE *pFile = fopen(path,"w");
        Employee* pEmployee = employee_new();
        if(pFile==NULL)
        {
            printf("Archivo inexistente\n");
        }
        else
        {
            longitud = ll_len(pArrayListEmployee);
            for(int i = 0; i < longitud; i++)
            {
                pEmployee = (Employee*) ll_get(pArrayListEmployee, i);

                fprintf(pFile, "%d, %s, %d, %d\n", pEmployee->id, pEmployee->nombre, pEmployee->horasTrabajadas, pEmployee->sueldo);    //Se escribe al archivo

            }
            respuesta = OK;
            fclose(pFile);
        }
    }

    return respuesta;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    int ret;
    ret = ERROR;
    FILE* pFile;
    pFile = fopen("data.bin", "wb");
    Employee* emp;

    if(ll_len(pArrayListEmployee)!= 0)
    {
        if(pArrayListEmployee != NULL)
        {
            for(int i = 0; i<ll_len(pArrayListEmployee);i++)
            {
                emp = (Employee*)ll_get(pArrayListEmployee, i);
                fwrite(emp, sizeof(Employee*), 1, pFile);
            }
            fclose(pFile);
            ret = OK;
        }
        else
        {
            printf("No hay Archivo\n");
            system("pause");
        }
     }
     else
     {
         printf("No hay Datos\n");
     }

    return ret;
}

int menuPpal()
{
    int r;
    do
    {
        system("cls");
        printf(" \n");
        printf("  Menu:                                                                          \n");
        printf("  1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).   \n");
        printf("  2. Cargar los datos de los empleados desde el archivo data.csv (modo binario). \n");
        printf("  3. Alta de empleado                                                            \n");
        printf("  4. Modificar datos de empleado                                                 \n");
        printf("  5. Baja de empleado                                                            \n");
        printf("  6. Listar empleados                                                            \n");
        printf("  7. Ordenar empleados                                                           \n");
        printf("  8. Guardar los datos de los empleados en el archivo data.csv (modo texto).     \n");
        printf("  9. Guardar los datos de los empleados en el archivo data.bin (modo binario).   \n");
        printf(" 10. Salir                                                                       \n");
        printf(" \n");
        scanf("%d", &r);
    }
    while(r < 1 || r > 10);

    return r;
}

int menuEdit()
{
    int r;

    do
    {
        system("cls");
        printf("***********************************\n");
        printf("     Seleccione un campo a editar: \n");
        printf("     1. Nombre.                    \n");
        printf("     2. Horas Trabajadas.          \n");
        printf("     3. Sueldo                     \n");
        printf("     4. Salir                      \n");
        printf("***********************************\n");
        scanf("%d", &r);
    }
    while(r < 1 || r > 4);

    return r;
}

int menuSort()
{
    int r;

    do
    {
        system("cls");
        printf("***********************************\n");
        printf("     Seleccione el sort:           \n");
        printf("     1. Id.                        \n");
        printf("     2. Nombre.                    \n");
        printf("     3. Horas Trabajadas.          \n");
        printf("     4. Sueldo                     \n");
        printf("     5. Salir                      \n");
        printf("***********************************\n");
        scanf("%d", &r);
    }
    while(r < 1 || r > 5);

    return r;
}

