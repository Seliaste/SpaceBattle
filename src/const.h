#ifndef CONST_H
#define CONST_H

/**
 * @brief définit le déplacement lateral d'un vaisseau
 *
 */
#define MOVING_STEP 6

/**
 * @brief définit la vitesse d'un ennemi
 *
 */
#define ENEMY_SPEED 1

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 640

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480

/**
 * \brief Taille d'un vaisseau
 */
#define SHIP_SIZE 32

/**
 * \brief Taille du missile
 */
#define MISSILE_SIZE 8

/**
 * @brief définit la vitesse d'un missile
 *
 */
#define MISSILE_SPEED 10

/**
 * @brief nombre d'ennemis
 *
 */
#define NB_ENEMIES 50

/**
 * @brief distance entre chaque vaisseau ennemi
 *
 */
#define VERTICAL_DIST 4 * SHIP_SIZE

/**
 * @brief temps entre la fin du jeu et la fermeture de l'app
 *
 */
#define EXIT_DELAY 3000 // 3s

/**
 * @brief Nombre de vies
 *
 */
#define LIVES 3

/**
 * @brief Nombre d'images dans l'animation d'explosion
 *
 */
#define EXPLOSION_FRAMES 5

/**
 * @brief Temps alloué à chaque image de l'animation d'explosion (en frame time)
 *
 */
#define EXPLOSION_FRAMETIME 10

/**
 * @brief Multiplicateur de la vitesse lors du mode difficile
 *
 */
#define HARDMODE_MULTIPLIER 2

#endif