#pragma once
#include <stdint.h>

#define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))

namespace Theme {
    namespace Color {
        // Vous pouvez définir ici vos couleurs personnalisées.
        // Utiliser la macro RGB565 rend le code plus lisible.

        // Couleurs de base
        constexpr uint16_t White      = RGB565(255, 255, 255);
        constexpr uint16_t Black      = RGB565(0, 0, 0);
        constexpr uint16_t Blue       = RGB565(0, 0, 255);
        constexpr uint16_t Green      = RGB565(0, 255, 0);
        constexpr uint16_t DarkGreen  = RGB565(0, 128, 0);
        constexpr uint16_t Red        = RGB565(255, 0, 0);
        constexpr uint16_t Yelow      = RGB565(255, 255, 0);

        // Couleurs personnalisées
        constexpr uint16_t Aquamarine = RGB565(127, 255, 212); 
        constexpr uint16_t RougeFonce = RGB565(184, 0, 0);  
        constexpr uint16_t RougeClaire= RGB565(255, 0, 0);    
        constexpr uint16_t Sienna     = RGB565(160, 82, 45);  
        constexpr uint16_t BleuCiel   = RGB565(165, 199, 232);
        constexpr uint16_t CadetBlue  = RGB565(95, 158, 255);

        // Couleurs pour le thème MODAL
        constexpr uint16_t ModalPurple      = RGB565(50, 18, 122);   // Indigo
        constexpr uint16_t ModalLilac       = RGB565(230, 230, 250); // Lavender
        constexpr uint16_t ModalAccent      = RGB565(147, 112, 219); // MediumPurple

        // Couleurs UI spécifiques
        constexpr uint16_t ModalOverlay = RGB565(0, 0, 0); // Noir pour l'overlay. On pourrait utiliser une couleur plus claire pour un effet transparent.

        // --- Couleurs pour le thème Océan ---
        constexpr uint16_t DeepOceanBlue    = RGB565(0, 8, 94);
        constexpr uint16_t SeafoamGreen     = RGB565(159, 255, 203);
        constexpr uint16_t SandyBeige       = RGB565(244, 222, 179);
        constexpr uint16_t CoralRed         = RGB565(255, 127, 80);
        constexpr uint16_t WhiteSand        = RGB565(253, 245, 230);
    }
}