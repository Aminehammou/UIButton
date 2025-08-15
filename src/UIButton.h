#ifndef UIButton_H
#define UIButton_H

#include "U8g2_for_TFT_eSPI.h"
#include "UIRect.h"
#include "UITextComponent.h"
#include "UIButtonStyle.h"
#include <TFT_eSPI.h>
#include <functional>

/**
 * @class UIButton
 * @brief Un composant de bouton cliquable pour l'interface utilisateur.
 *
 * Cette classe représente un bouton qui peut être pressé, relâché et glissé.
 * Il peut avoir différents styles pour différents états et peut avoir des rappels pour les événements de pression et de relâchement.
 */
class UIButton : public UITextComponent {
public:
    /**
     * @brief Construit un nouvel objet UIButton.
     *
     * @param u8f Référence à l'objet U8g2_for_TFT_eSPI pour le rendu des polices.
     * @param rect Le rectangle définissant la position et la taille du bouton.
     * @param label Le texte à afficher sur le bouton.
     * @param style Le style du bouton.
     * @param onPressCallback Fonction de rappel optionnelle à appeler lorsque le bouton est pressé.
     * @param onReleaseCallback Fonction de rappel optionnelle à appeler lorsque le bouton est relâché.
     */
    UIButton(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& label,
             const UIButtonStyle& style,
             std::function<void()> onPressCallback = nullptr,
             std::function<void()> onReleaseCallback = nullptr);

    /**
     * @brief Gère l'événement de pression.
     *
     * @param tft Référence à l'objet TFT_eSPI.
     * @param tx La coordonnée x du toucher.
     * @param ty La coordonnée y du toucher.
     */
    void handlePress(TFT_eSPI& tft, int tx, int ty) override;

    /**
     * @brief Gère l'événement de relâchement.
     *
     * @param tft Référence à l'objet TFT_eSPI.
     * @param tx La coordonnée x du toucher.
     * @param ty La coordonnée y du toucher.
     */
    void handleRelease(TFT_eSPI& tft, int tx, int ty) override;

    /**
     * @brief Gère l'événement de glissement.
     *
     * @param tft Référence à l'objet TFT_eSPI.
     * @param tx La coordonnée x du toucher.
     * @param ty La coordonnée y du toucher.
     */
    void handleDrag(TFT_eSPI& tft, int tx, int ty) override;

    /**
     * @brief Définit le style du bouton.
     *
     * @param newStyle Le nouveau style à appliquer.
     */
    void setStyle(const UIButtonStyle& newStyle);

    /**
     * @brief Définit la fonction de rappel pour l'événement de pression.
     *
     * @param onPressCallback La fonction de rappel.
     */
    void onPress(std::function<void()> onPressCallback);

    /**
     * @brief Définit la fonction de rappel pour l'événement de relâchement.
     *
     * @param onReleaseCallback La fonction de rappel.
     */
    void onRelease(std::function<void()> onReleaseCallback);

private:
    /**
     * @brief Dessine le bouton à l'écran.
     *
     * @param tft Référence à l'objet TFT_eSPI.
     * @param force True pour forcer un redessin, false sinon.
     */
    void drawInternal(TFT_eSPI& tft, bool force) override;

    UIButtonStyle _style; ///< Le style du bouton.
    bool _pressed = false; ///< True si le bouton est actuellement pressé, false sinon.

    std::function<void()> _onPressCallback; ///< Fonction de rappel pour l'événement de pression.
    std::function<void()> _onReleaseCallback; ///< Fonction de rappel pour l'événement de relâchement.
};

#endif // UIButton_H