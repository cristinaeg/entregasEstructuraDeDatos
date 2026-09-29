# entregasEstructuraDeDatos

# Juego de Cartas: Color, Alto o Bajo 🃏

Este repositorio contiene la implementación de un juego de cartas multijugador desarrollado como parte de las entregas de la asignatura de **Estructuras de datos**. El juego simula una partida estratégica donde los jugadores compiten en rondas utilizando cartas de colores y números, basándose en condiciones cambiantes dictadas por el jugador inicial.

## 📜 Reglas del Juego

### Componentes
* **El Mazo:** Está compuesto por 40 cartas en total.
* **Atributos de las cartas:** 
  * **Color:** Amarillo, Rojo, Verde o Azul (10 cartas por color).
  * **Valor numérico:** Del 1 al 10.
* **Jugadores:** De 2 a 10 jugadores por partida.

### Preparación
1. Se baraja el mazo.
2. Se reparten **4 cartas** a cada jugador al inicio de la partida.

### Dinámica de la Ronda
1. **El Turno del Jugador 1:** El Jugador 1 inicia la ronda. Elige una carta de su mano y la coloca boca abajo sobre la mesa.
2. **La Declaración:** Al poner su carta, el Jugador 1 debe decir en voz alta:
   * Un **color** (Amarillo, Rojo, Verde o Azul).
   * Una **condición**: "Más alto" o "Más bajo".
3. **Respuesta de los demás jugadores:** Cada uno de los jugadores restantes elige una carta de su mano estratégica mente para competir y la coloca boca abajo.
4. **Resolución de la ronda:** Una vez que todos han puesto su carta, todas se voltean al mismo tiempo.
5. **Ganador de la ronda:** Gana la carta que **coincida con el color declarado** por el Jugador 1 y que, entre las de ese color, tenga el valor numérico **más alto o más bajo** (según la condición declarada).
   * *Nota:* El ganador de la ronda recolecta todas las cartas jugadas en esa mesa. Estas cartas ganadas se guardan en el pozo de puntuación del ganador y ya no vuelven a entrar en juego.

### Fin del Juego
* Las rondas continúan (exactamente 4 rondas, ya que cada jugador empieza con 4 cartas) hasta que los jugadores se quedan sin cartas en la mano.
* El ganador absoluto de la partida es el jugador que al final haya recolectado la **mayor cantidad de cartas**.

---

## 🛠️ Diseño y Arquitectura (Estructuras de datos)

Para la implementación de este juego, se aplican los siguientes conceptos de **Estructuras de datos**:

* **Mazo de cartas (`Stack` / Pila o `List` / Lista):** Para almacenar las 40 cartas iniciales, permitir el barajado (shuffle) y repartir eficientemente.
* **Mano de los Jugadores (`List` o `Array`):** Una estructura dinámica que se va reduciendo a medida que los jugadores juegan sus cartas.
* **Cartas jugadas en la mesa (`Queue` o `Array`):** Para recolectar temporalmente las cartas puestas boca abajo en una ronda antes de ser evaluadas.
* **Pozo de puntuación (`Integer` o `List`):** Cada jugador necesita un contador o una lista adicional para almacenar las cartas que ha ganado y así calcular el ganador al final de la partida.
* **Objetos / Nodos (`Card`):** Cada carta es una estructura que encapsula dos propiedades: `Color` (Enum o String) y `Valor` (Integer).

## 🚀 Requisitos y Ejecución

* **Lenguaje:**  C++ 
* **Dependencias:** Ninguna,

**Para ejecutar el juego en consola:**
```bash
# 1. Clonar el repositorio
git clone [https://github.com/cristinaeg/entregasEstructuraDeDatos.git](https://github.com/cristinaeg/entregasEstructuraDeDatos.git)

# 2. Navegar al directorio del proyecto
cd entregasEstructuraDeDatos

# 3. Compilar / Ejecutar el juego

