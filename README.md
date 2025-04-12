# Sistema de Gestión de tickets de Soporte Tecnico

## Descripción

Este sistema permite gestionar la atencion de tickets de un servicio de soporte tecnico. El usuario puede registrar un ticket un id unico, asignarle prioridad (baja(1), media(2) o alta(3)), mostrar los id de los tickets que no han sido atendidos, atender al siguiente ticket segun su prioridad y su hora de asignacion de prioridad, y buscar un ticket y mostrar sus datos segun su id.

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack** de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

### Pasos para compilar y ejecutar:

1. **Descarga y descomprime el** archivo `.zip` en una carpeta de tu elección.
2. **Abre el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code.
    - Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde descomprimiste el proyecto.
3. **Compila el código**
    - Abre el archivo principal (`tarea1.c`).
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando (ajusta el nombre si el archivo principal tiene otro nombre):
        
        ```powershell
        gcc extra.c list.c tarea1.c -Wno-unused-result -o tarea1
        ```
        
4. **Ejecuta el programa**
    - Una vez compilado, puedes ejecutar la aplicación con:
        
        ```
        ./tarea1
        ```
        

## Funcionalidades

### Funcionando correctamente:

- Registrar tickets con un id, descripcion breve del problema, registrar su hora de ingreso y asignarles prioridad baja de manera automatica.
- Modificar la prioridad de los pacientes, independiente de cual sea su prioridad actual, actualizando su hora.
- Ver la lista de espera de tickets, ordenada por prioridad y hora de registro.
- Atender al siguiente ticket, respetando el orden de prioridad.

### Problemas conocidos:

- Al registrar un ticket, el id debe ser un numero entero, sino se registrara pero no podra utilizarse con las demas funciones.

### A mejorar:

- Implementar una interfaz de usuario más amigable.
- Permitir la edición de los datos de los pacientes.

## Ejemplo de uso

**Paso 1: Registrar un Nuevo ticket**

Se comienza registrando un nuevo ticket recien llegado al soporte tecnico.

```
Opción seleccionada: 1) Registrar ticket
Ingrese ID: 1
Ingresee descripcion del problema: falla total del sistema
```

El sistema registra el ticket con el id 1 y lo guarda en la lista de tickets con prioridad baja.
Si el id del ticket ya se encuentra registrado, el ticket no se guarda y se imprime el mensaje "ID ya fue registrado".

**Paso 2: Asignar Prioridad a un Ticket**

Tras una evaluación inicial, el tecnico indica la prioridad de atencion del problema.

```
Opción seleccionada: 2) Asignar prioridad a ticket
Ingrese id de ticket para asignar prioridad: 1
Seleccione el nuevo nivel de prioridad (Alto(3), Medio(2), Bajo(1)): 3
```

El sistema actualiza la prioridad del ticket con id 1 a Alta. Para facilitar la reasignacion de prioridad el sistema recibe un numero de 1 a 3, siendo 1 prioridad baja, 2 media y 3 alta. El programa indica si el id ingresado no se encuentra en la lista de tickets pendientes y tambien si la nueva prioridad asignada no es un numero valido o si es el mismo de su prioridad actual.

**Paso 3: Ver la Lista de Espera**

El usuario revisa la lista de espera para ver todos los tickets y sus prioridades.

```
Opción seleccionada: 3) Mostrar lista de espera
```

La lista muestra el id 1, del ticket con ese id que esta actualmente en la lista de prioridad alta.

**Paso 4: Atender al Siguiente ticket**

El cliente con el ticket id 1 es llamado para ser atendido.

```
Opción seleccionada: 4) Atender al siguiente ticket
```

El sistema muestra que el cliente con el ticket con id 1 está siendo atendido y lo elimina de la lista de espera.

**Paso 5: Buscar ticket por ID**

Si fueron ingresados mas tickets y se quiere buscar uno en especifico, el usuario debe ingresar el id deseado y el programa mostrara los datos del ticket. Usaremos de ejemplo un ticket con id 3

```
Opción seleccionada: 5) Buscar ticket por ID
Ingrese ID de ticket deseado: 3
```
El programa muestra el ticket con id 3, la descripcion de su problema, su prioridad de atencion y la hora en la que se le asigno prioridad o en la que fue registrado si no hubo cambio de prioridad. Se indica tambien si el id ingresado por el usuario no esta registrado aun.
