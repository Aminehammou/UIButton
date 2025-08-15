#include "UIButton.h"

// Décommentez la ligne suivante pour activer les messages de débogage pour cette classe
// #define DEBUG_UIBUTTON

UIButton::UIButton(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& label,
                   const UIButtonStyle& style,
                   std::function<void()> onPressCallback,
                   std::function<void()> onReleaseCallback)
    : UITextComponent(u8f, rect, label),
      _style(style),
      _pressed(false),
      _onPressCallback(onPressCallback),
      _onReleaseCallback(onReleaseCallback) {
}

void UIButton::drawInternal(TFT_eSPI& tft, bool force) {
    // La méthode de dessin est maintenant `drawInternal` pour respecter la classe de base.
    uint16_t fill, outline, text_color;

    // 1. Sélectionner les couleurs en fonction de l'état (activé, pressé, normal)
    if (!enabled) {
        fill = _style.disabledFillColor;
        outline = _style.disabledOutlineColor;
        text_color = _style.disabledTextColor;
    } else if (_pressed) {
        fill = _style.pressedFillColor;
        outline = _style.pressedOutlineColor; // Utiliser la couleur de contour normale pour l'état pressé
        text_color = _style.pressedTextColor;
    } else {
        fill = _style.fillColor;
        outline = _style.outlineColor;
        text_color = _style.textColor;
    }

    // 2. Dessiner la forme du bouton
    tft.fillRoundRect(rect.x, rect.y, rect.w, rect.h, _style.cornerRadius, fill);
    tft.drawRoundRect(rect.x, rect.y, rect.w, rect.h, _style.cornerRadius, outline);

    // 3. Configurer les propriétés du texte pour U8g2
    _u8f.setFontMode(1);                    // Mode transparent pour le fond du texte
    _u8f.setFontDirection(0);               // Texte de gauche à droite
    _u8f.setForegroundColor(text_color);    // U8g2_for_TFT_eSPI utilise la couleur de premier plan de TFT_eSPI
    _u8f.setBackgroundColor(fill);          // La couleur de fond est gérée par le mode transparent
    _u8f.setFont(_style.font);              // Utilise la police U8g2 définie dans le style

    // 4. Calculer la position du texte (U8g2 n'a pas de datums comme TFT_eSPI)
    int textX, textY;
    int16_t textW = _u8f.getUTF8Width(_text.c_str());
    int16_t textH = _u8f.getFontAscent() - _u8f.getFontDescent();

    // Alignement horizontal
    switch (_style.textAlign) {
        case TL_DATUM: case ML_DATUM: case BL_DATUM:
        default:
            textX = rect.x + _style.padding;
            break;
        case TC_DATUM: case MC_DATUM: case BC_DATUM:
            textX = rect.x + (rect.w - textW) / 2;
            break;
        case TR_DATUM: case MR_DATUM: case BR_DATUM:
            textX = rect.x + rect.w - textW - _style.padding;
            break;
    }

    // Alignement vertical (u8f dessine depuis la baseline)
    switch (_style.textAlign) {
        case TL_DATUM: case TC_DATUM: case TR_DATUM:
            textY = rect.y + _u8f.getFontAscent() + _style.padding;
            break;
        case ML_DATUM: case MC_DATUM: case MR_DATUM:
        default:
            // Centrage vertical approximatif
            textY = rect.y + (rect.h + textH) / 2;
            break;
        case BL_DATUM: case BC_DATUM: case BR_DATUM:
            textY = rect.y + rect.h - _u8f.getFontDescent() - _style.padding;
            break;
    }

    // 5. Dessiner le texte
    _u8f.setCursor(textX, textY);
    _u8f.print(_text);
}

void UIButton::handlePress(TFT_eSPI& tft, int tx, int ty) {
    // Ne rien faire si le bouton est désactivé, si le clic est en dehors, ou s'il est déjà pressé.
    if (!enabled || !contains(tx, ty) || _pressed) {
        return;
    }

    #ifdef DEBUG_UIBUTTON
    Serial.print("handlePress: "); Serial.println(_text);
    #endif

    _pressed = true;
    setDirty(true);      // Marque pour un redessin au prochain cycle

    if (_onPressCallback) {
        _onPressCallback();
    }
}

void UIButton::handleRelease(TFT_eSPI& tft, int tx, int ty) {
    bool wasPressed = _pressed;
    _pressed = false; // Le bouton n'est plus considéré comme pressé

    if (wasPressed) {
        #ifdef DEBUG_UIBUTTON
        Serial.print("handleRelease: "); Serial.println(_text);
        #endif
        setDirty(true);  // Marque pour redessinage pour restaurer l'état normal

        // Déclencher l'action uniquement si le doigt est relâché À L'INTÉRIEUR du bouton
        if (contains(tx, ty) && _onReleaseCallback) {
            #ifdef DEBUG_UIBUTTON
            Serial.println("  -> Action onRelease declenchee.");
            #endif
            _onReleaseCallback();
        }
    }
}

void UIButton::handleDrag(TFT_eSPI& tft, int tx, int ty) {
    // Gère le cas où l'utilisateur glisse son doigt hors du bouton tout en maintenant la pression.
    // Cela rend l'interface plus intuitive.
    if (enabled) {
        bool isInside = contains(tx, ty);
        if (_pressed != isInside) {
            #ifdef DEBUG_UIBUTTON
            Serial.printf("handleDrag: %s - _pressed change a : %d\n", _text.c_str(), isInside);
            #endif
            _pressed = isInside;
            setDirty(true); // Marquer pour redessinage
        }
    }
}

void UIButton::setStyle(const UIButtonStyle& newStyle) {
    _style = newStyle;
    setDirty(true);
}

void UIButton::onPress(std::function<void()> onPressCallback) {
    _onPressCallback = onPressCallback;
}

void UIButton::onRelease(std::function<void()> onReleaseCallback) {
    _onReleaseCallback = onReleaseCallback;
}
