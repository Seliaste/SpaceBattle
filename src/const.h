#ifndef CONST_H
#define CONST_H

/**
 * @brief définit le déplacement lateral d'un vaisseau
 * 
 */
#define MOVING_STEP 5

#define MISSILE_SPEED 10
/**
 * @brief définit la vitesse d'un ennemi
 *
 */
#define ENEMY_SPEED 2

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
 */
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

/**
 * @brief nombre d'ennemis
 * 
 */
#define NB_ENEMIES 20

/**
 * @brief distance entre chaque vaisseau ennemi
 * 
 */
#define VERTICAL_DIST 3*SHIP_SIZE

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

#endif