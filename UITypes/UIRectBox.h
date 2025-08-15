#ifndef UIRECTBOX_H
#define UIRECTBOX_H

#include "UIRect.h"

/**
 * @class UIRectBox
 * @brief Un helper pour UIRect qui fournit des fonctions utilitaires comme la vérification d'intersection.
 * Cela permet de conserver UIRect comme une simple structure de données (POD).
 */
class UIRectBox {
public:
    /**
     * @brief Vérifie si deux rectangles s'intersectent.
     * @return true si les rectangles se chevauchent, false sinon.
     */
    static bool intersects(const UIRect& r1, const UIRect& r2) {
        return (r1.x < r2.x + r2.w && r1.x + r1.w > r2.x && r1.y < r2.y + r2.h && r1.y + r1.h > r2.y);
    }
};

#endif // UIRECTBOX_H