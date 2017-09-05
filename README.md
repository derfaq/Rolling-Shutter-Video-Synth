# Rolling Shutter Video Synth

*Rolling Shutter Video Synth (RS-VS)* se referire a todos aquellos dispositivos capaces de producir imagenes y videos a través de la interferencia entre la luz pulsante de un led (luz estroboscopica, flicker) y el *scan rate* de una cámara digital (CMOS).

>Este repositorio se encuentra **en construcción** y la intención del mismo es poner a disposición de la comunidad esquemas y software siguiendo la filosofía open hardware y open software. Sientasé libre de copiar, distribuir, modificar y construir su propio RS-VS!.  
>La comunidad crece con la colaboración: el repositorio se encuentra **abierto** a todos aquellos que quieran contribuir, desde dejar  links, datos sobre frecuencias y cámaras, traducciones, tutoriales, modificar piezas de software para agregar nuevas funcionalidades, etc.

## Advertencia
El parpadeo/flicker de luz puede afectar la salud de aquellas personas que sufran [epilepsia fotosensitiva](https://es.wikipedia.org/wiki/Epilepsia_fotosensitiva).

[ ![Homero epilepsia](https://img.youtube.com/vi/4RGrcWkNlGE/0.jpg) ](https://youtu.be/4RGrcWkNlGE)  
*Simpsons - 10x23 Treinta minutos sobre Tokio*

## Configuración básica  

### Hardware
Hacer un RS-VS con Arduino es muy sencillo, en su configuración mas simple solo necesita:
+ Arduino UNO (o cualquiera basado en el micro ATmega328)
+ Un LED
+ Una resistencia de entre 150/220/470 ohms, para limitar la corriente del led
+ Dos potenciometros de 10k ohms, para ajustar la frecuencia del flicker y la cantidad de líneas.
+ Un celular con cámara :iphone:

![schematic](/SimplePWM_RS-VS/SimplePWM_RS-VS.png)

### Software
Descargue y descomprima este repostorio en su pc, y cargue el scketch que se encuentra en `/SimplePWM_RS-VS/SimplePWM_RS-VS.ino`.  

![download](/img/download.png)  

### Uso: Tips and tricks
+ Una vez cargado el sketch, acerque la cámara del celular lo mas posible al led. Posiblemente vea algo similar a esto:  
![001](/img/001.png)  
Regule el potenciometro conectado a A1 para fijar la cantidad de lineas en la pantalla, y ajuste el potenciometro conectado a A0 hasta que obtenga una imagen estática, si no lo consigue pruebe modificar la frecuencia de la cámara en el scketch `F_CAM = 30` por `F_CAM = 25` o algún valor intermedio y vuelva a cargarlo.  
+ Para lograr un mayor contraste en la imágen, puede (si su cámara lo permite) aumentar la sensibilidad fotográfica (ISO), que en definitiva, significa aumentar la ganancia del sensor de imagen CMOS. En mi caso (Samsung S4 mini, GT-I9190) esto se logra de la siguiente manera:  
![002](/img/002.png)  
*Configuración*  
![003](/img/003.png)  
*ISO*  
![004](/img/004.png)  
*ISO = 800*  
+ Para lograr mayor uniformidad en las líneas, es conveniente recubrir el led con un trozo de barra de silicona.   
![009](/img/009.png)  
*Led RGB recubierto con un trozo de barra de silicona. Para introducirlo en la barra se realizó un perforación de 5mm*  
![006](/img/006.png)  
*Silicona + ISO*  
+ Otra manera de mejorar la imagen es reducir el tiempo de exposición, es decir el tiempo en que un pixel recolecta luz. Esto se suele modificar para que las fotos "no salgan movidas". En mi caso, este modo de operación se llama "Deportes":  
![005](/img/005.png)  
*Automático con silicona (sin ISO)*  
![007](/img/007.png)  
*Misma imagen en modo deportes*   
+ Regulando el potenciometro conectado a A1 controlamos la cantidad de líneas:   
![008](/img/008.png)  
*16 líneas*  


## Más
¡Hay muchas mas cosas que se pueden hacer!, dibujar unas líneas con un led esta bien, pero ¿como variar el ancho de la línea/pulso? ¿y si el ancho varía de línea en línea? ¿y si le agregamos otros colores? ¿podemos enviar información o alguna clase de código al celular? ¿que otras maneras hay de generar este efecto sin usar arduino?.  
En este repositorio encontrará distintas carpetas con sketchs con diversas funcionalidades. Cada carpeta además, contiene un archivo para [Fitzing](http://fritzing.org/home/) el cual posee el esquemático y el dibujo del circuito, y un archivo README con una breve explicación del funcionamiento.  
De momento estos son los sketchs disponibles:
+ **Simple PWM RS-VS**: genera una onda cuadrada cuya frecuencia depende del scan rate de la camara y la cantidad de líneas que querramos dibujar sobre la pantalla.
+ **Full PWM RS-VS**: genera una señal PWM, cuya frecuencia depende del scan rate de la camara y la cantidad de líneas y además podemos variar el ancho del pulso/ancho de la línea.



---

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Licencia Creative Commons" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /> © 2017 Facundo Daguerre, esta documentación está bajo una <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Licencia Creative Commons Atribución 4.0 Internacional</a>.
