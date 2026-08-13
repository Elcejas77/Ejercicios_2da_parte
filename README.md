# Estructuras-Computacionales

Proyectos realizados en el curso de **Estructuras Computacionales**
(STM32, lenguaje C, STM32CubeIDE) sobre la placa **Nucleo-L476RG**.

Repositorio unificado que reúne los ejercicios, preparciales y exámenes del
curso. Cada proyecto es un firmware independiente para STM32CubeIDE.

## Proyectos

| Proyecto | Descripción |
|---|---|
| [ejercicio_parte2](ejercicio_parte2/) | Ejercicios de la segunda parte del curso: implementación de un ring buffer reutilizable. |
| [preparcial1](preparcial1/) | Preparcial #1: control de luces (LEDs) con botones e interrupciones. |
| [mid_term_exam](mid_term_exam/) | Examen parcial: sistema de señales direccionales (luces de giro izquierda/derecha, USART2 de depuración). |
| [final_exam](final_exam/) | Examen final: sistema de operaciones aritméticas con teclado hexadecimal, display OLED (SSD1306) y USART2. |

## Requisitos

- STM32CubeIDE (o toolchain ARM/GCC compatible).
- Placa de desarrollo **STM32 Nucleo-L476RG**.

## Cómo abrir un proyecto

1. Abre STM32CubeIDE.
2. *File → Import → Existing Projects into Workspace*.
3. Selecciona la carpeta del proyecto (p. ej. `ejercicio_parte2/`) y acepta.
4. Compila y ejecuta.

Cada carpeta contiene su propio proyecto `.ioc` y configuración de
STM32CubeIDE.
