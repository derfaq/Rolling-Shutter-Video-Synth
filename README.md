## Rolling Shutter Video Synth

*Rolling Shutter Video Synth (RS-VS)* se referire a todos aquellos dispositivos capaces producir imagenes y videos a través de la interferencia entre la luz pulsante de un led (estroboscopica, flicker) y el scan rate de una cámara digital CMOS (como la de los celulares).

>Este repositorio se encuentra **en construcción** y la intención del mismo es poner a disposición de la comunidad esquemas y software siguiendo la filosofía open hardware y open software. Sientasé libre de copiar, distribuir, modificar y construir su propio RS-VS!.  
>
La comunidad crece con la colaboración: el repositorio se encuentra **abierto** a todos aquellos que quieran contribuir, desde dejar  links, datos sobre frecuencias y camaras, traducciones, tutoriales, modificar piezas de software para agregar nuevas funcionalidades, etc.

### Advertencia
EL parpadeo/flicker de luz puede afectar la salud de aquellas personas que sufran [epilepsia fotosensitiva](https://es.wikipedia.org/wiki/Epilepsia_fotosensitiva).

[ ![Homero epilepsia](https://img.youtube.com/vi/4RGrcWkNlGE/0.jpg) ](https://youtu.be/4RGrcWkNlGE)  
*Simpsons - 10x23 Treinta minutos sobre Tokio*

### Configuración básica
#### Hardware
Hacer un RS-VS con Arduino es muy sencillo, en su configuración mas simple solo necesitamos:
+ Arduino UNO (o cualquiera basado en el micro ATmega328)
+ Un LED
+ Una resistencia de entre 150/220/470 ohms, para limitar la corriente del led
+ Un potenciometro de 10k ohms, para ajustar la frecuencia del flicker
+ Un celular con cámara  
