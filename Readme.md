# Librairie UIButton

Une librairie C++ simple pour créer des boutons interactifs sur des écrans TFT avec les librairies `TFT_eSPI` et `U8g2_for_TFT_eSPI`.

## Fonctionnalités

*   **Gestion d'états :** Normal, pressé et désactivé.
*   **Apparence personnalisable :** Couleurs, coins arrondis, polices, alignement du texte, etc.
*   **Callbacks pour les événements :** Actions distinctes pour `onPress` (appui) et `onRelease` (relâchement).
*   **Gestion intelligente du toucher :** Gère le glissement du doigt hors du bouton pour annuler une action.
*   **Rendu optimisé :** Le bouton ne se redessine que lorsque son état change pour éviter le scintillement.

## Dépendances

### Librairies externes

*   **Arduino Framework** (`Arduino.h`)
*   **[TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)**: Pour le rendu graphique sur l'écran TFT.
*   **[U8g2_for_TFT_eSPI](https://github.com/Bodmer/U8g2_for_TFT_eSPI)**: Pour la gestion des polices de caractères.
*   **Bibliothèque Standard C++**: `<functional>` pour les callbacks.

### Fichiers internes du projet

La classe `UIButton` dépend d'autres composants de ce framework UI :

*   `UITextComponent.h`: La classe de base pour les composants textuels.
*   `UIButtonStyle.h`: La structure qui définit l'apparence du bouton.
*   `UIRect.h`: Une structure simple pour définir les rectangles (position et taille).
*   `Theme.h`: Pour la gestion globale des thèmes et des couleurs.

## Exemple d'utilisation complet

Voici un exemple autonome que vous pouvez utiliser directement.

```cpp
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "U8g2_for_TFT_eSPI.h"
#include "UIButton.h" // Assurez-vous que le chemin est correct

// Initialisation des objets graphiques
TFT_eSPI tft = TFT_eSPI();
U8g2_for_TFT_eSPI u8f = U8g2_for_TFT_eSPI(&tft);

// Déclaration du bouton
UIButton button;

void setup() {
    Serial.begin(115200);

    // Initialisation de l'écran et de la police
    tft.init();
    tft.setRotation(1); // Ajustez la rotation selon votre écran
    tft.fillScreen(TFT_BLACK);

    u8f.begin();
    // Sélectionnez une police de U8g2
    u8f.setFont(u8g2_font_ncenB10_tr); 

    // 1. Définir le style du bouton
    UIButtonStyle buttonStyle;
    buttonStyle.fillColor           = TFT_BLUE;
    buttonStyle.outlineColor        = TFT_WHITE;
    buttonStyle.textColor           = TFT_WHITE;
    buttonStyle.pressedFillColor    = TFT_SKYBLUE;
    buttonStyle.pressedTextColor    = TFT_BLACK;
    buttonStyle.disabledFillColor   = TFT_DARKGREY;
    buttonStyle.disabledTextColor   = TFT_LIGHTGREY;
    buttonStyle.cornerRadius        = 8;
    buttonStyle.font                = u8g2_font_ncenB10_tr;
    buttonStyle.textAlign           = MC_DATUM; // Texte centré
    buttonStyle.padding             = 10;

    // 2. Définir la position et la taille
    UIRect buttonRect = {tft.width() / 2 - 75, tft.height() / 2 - 25, 150, 50};

    // 3. Définir les actions (callbacks)
    auto onPressAction = []() {
        Serial.println("Bouton Pressé !");
    };

    auto onReleaseAction = []() {
        Serial.println("Bouton Relâché ! Action déclenchée.");
        // Mettez ici le code à exécuter lors du clic
    };

    // 4. Créer l'instance du bouton
    button = UIButton(u8f, buttonRect, "Cliquez-moi", buttonStyle, onPressAction, onReleaseAction);

    // 5. Dessiner le bouton initialement
    button.draw(tft, true); 
}

void loop() {
    uint16_t x, y;
    bool isTouching = tft.getTouch(&x, &y);

    // Gérer les états du bouton en fonction du toucher
    if (isTouching) {
        button.handlePress(tft, x, y);
        button.handleDrag(tft, x, y);
    } else {
        button.handleRelease(tft, x, y);
    }

    // Redessiner le bouton uniquement si son état a changé
    button.draw(tft, button.isDirty());

    delay(20); // Petit délai pour la stabilité
}
```

## Référence de l'API

### La structure `UIButtonStyle`

Cette structure contient toutes les options pour personnaliser l'apparence d'un bouton.

| Propriété              | Type                 | Description                                           |
| ---------------------- | -------------------- | ----------------------------------------------------- |
| `fillColor`            | `uint16_t`           | Couleur de fond (état normal)                         |
| `outlineColor`         | `uint16_t`           | Couleur du contour (état normal)                      |
| `textColor`            | `uint16_t`           | Couleur du texte (état normal)                        |
| `pressedFillColor`     | `uint16_t`           | Couleur de fond (état pressé)                         |
| `pressedOutlineColor`  | `uint16_t`           | Couleur du contour (état pressé)                      |
| `pressedTextColor`     | `uint16_t`           | Couleur du texte (état pressé)                        |
| `disabledFillColor`    | `uint16_t`           | Couleur de fond (état désactivé)                      |
| `disabledOutlineColor` | `uint16_t`           | Couleur du contour (état désactivé)                   |
| `disabledTextColor`    | `uint16_t`           | Couleur du texte (état désactivé)                     |
| `cornerRadius`         | `uint8_t`            | Rayon des coins arrondis.                             |
| `font`                 | `const uint8_t*`     | Pointeur vers une police U8g2.                        |
| `textAlign`            | `uint8_t`            | Alignement du texte (ex: `MC_DATUM`, `TL_DATUM`).     |
| `padding`              | `uint8_t`            | Marge intérieure en pixels entre le texte et le bord. |

### Constructeur `UIButton`

Crée une nouvelle instance de bouton.

```cpp
UIButton(
    U8g2_for_TFT_eSPI& u8f,
    const UIRect& rect,
    const String& label,
    const UIButtonStyle& style,
    std::function<void()> onPressCallback = nullptr,
    std::function<void()> onReleaseCallback = nullptr
);
```

### Méthodes principales

*   **`void draw(TFT_eSPI& tft, bool force = false)`**  
    Dessine le bouton. Mettez `force` à `true` pour forcer un redessin même si l'état n'a pas changé.

*   **`void handlePress(TFT_eSPI& tft, int tx, int ty)`**  
    Gère l'événement d'appui.

*   **`void handleRelease(TFT_eSPI& tft, int tx, int ty)`**  
    Gère l'événement de relâchement.

*   **`void handleDrag(TFT_eSPI& tft, int tx, int ty)`**  
    Gère l'événement de glissement.

*   **`void setStyle(const UIButtonStyle& newStyle)`**  
    Change le style du bouton et le marque pour un redessin.

*   **`void setText(const String& text)`**  
    Change le texte du bouton.

*   **`void setEnabled(bool enabled)`**  
    Active ou désactive le bouton.
