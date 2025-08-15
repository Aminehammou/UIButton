#include <Arduino.h>
#include <TFT_eSPI.h>
#include "U8g2_for_TFT_eSPI.h"
#include "UIButton.h"

TFT_eSPI tft = TFT_eSPI();
U8g2_for_TFT_eSPI u8f = U8g2_for_TFT_eSPI(&tft);

UIButton button;

void setup() {
    Serial.begin(115200);

    tft.init();
    tft.setRotation(1);

    u8f.begin();
    u8f.setFont(u8g2_font_helvB08_tf);

    // Définir le style du bouton
    UIButtonStyle buttonStyle = {
        .fillColor = TFT_WHITE,
        .outlineColor = TFT_BLACK,
        .textColor = TFT_BLACK,
        .disabledFillColor = TFT_LIGHTGREY,
        .disabledOutlineColor = TFT_OLIVE,
        .disabledTextColor = TFT_DARKGREY,
        .pressedFillColor = TFT_BLUE,
        .pressedOutlineColor = TFT_BLACK,
        .pressedTextColor = TFT_WHITE,
        .cornerRadius = 5,
        .padding = 10,
        .font = u8g2_font_helvB08_tf,
        .textAlign = MC_DATUM // Centre le texte horizontalement et verticalement
    };

    // Définir le rectangle du bouton (position et taille)
    UIRect buttonRect = {10, 50, 100, 40};

    // Définir les actions à effectuer lors du press et du release
    auto onPressAction = []() {
        Serial.println("Bouton pressé !");
    };

    auto onReleaseAction = []() {
        Serial.println("Bouton relâché !");
    };

    // Créer le bouton
    button = UIButton(u8f, buttonRect, "Mon Bouton", buttonStyle, onPressAction, onReleaseAction);

    button.draw(tft, true); // Dessiner initialement le bouton
}

void loop() {
    // Mettre à jour les informations tactiles
    uint16_t x, y;
    if (tft.getTouch(&x, &y)) {
        button.handlePress(tft, x, y);
        button.handleDrag(tft, x, y);
    } else {
        button.handleRelease(tft, x, y);
    }

    // Dessiner le bouton
    button.draw(tft, button.isDirty()); // Force le redessin uniquement si le bouton est dirty

    delay(10);
}