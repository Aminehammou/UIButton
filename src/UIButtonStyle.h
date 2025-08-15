#ifndef UIBUTTONSTYLE_H
#define UIBUTTONSTYLE_H

#include <TFT_eSPI.h> // Pour les définitions de couleurs comme TFT_WHITE
#include "Theme.h" // Remplacer l'ancien include par le nouveau fichier de thème
//#include "ThemeManager.h"

/**
 * @struct UIButtonStyle
 * @brief Définit l'apparence visuelle d'un composant UIButton.
 * 
 * Cette structure regroupe toutes les propriétés de style d'un bouton,
 * permettant de découpler l'apparence de la logique du composant.
 * Les valeurs par défaut correspondent au style original.
 */
struct UIButtonStyle {
    // Couleurs pour l'état normal (non pressé)
    uint16_t fillColor        = TFT_DARKGREY;
    uint16_t outlineColor     = TFT_WHITE;
    uint16_t textColor        = TFT_WHITE;

    // Couleurs pour l'état pressé
    uint16_t pressedFillColor    = TFT_WHITE;
    uint16_t pressedOutlineColor = TFT_DARKGREY;
    uint16_t pressedTextColor    = TFT_DARKGREY;

    // Couleurs pour l'état désactivé
    uint16_t disabledFillColor    = TFT_DARKGREY;
    uint16_t disabledOutlineColor = TFT_DARKGREY;
    uint16_t disabledTextColor    = TFT_LIGHTGREY;

    // Propriétés de la forme et de la police
    uint8_t cornerRadius = 6;
    const uint8_t* font  = nullptr;  // Police U8g2 (remplace fontId)
    uint8_t textAlign    = MC_DATUM; // Par défaut : Milieu-Centre
    uint8_t padding      = 5;        // Marge intérieure en pixels

    uint16_t confirmButtonStyle = TFT_RED;

};

#endif // UIBUTTONSTYLE_H
