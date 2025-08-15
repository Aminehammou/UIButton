# Documentation de la classe `UIButton`

## 1. Introduction

La classe `UIButton` est un composant fondamental de la librairie graphique. Elle permet de créer des boutons interactifs, cliquables, avec un texte, un style personnalisable et des actions associées à la pression (`onPress`) et au relâchement (`onRelease`).

Elle hérite de `UITextComponent`, ce qui lui donne la capacité de gérer du texte, et indirectement de `UIComponent`, ce qui lui permet d'être gérée automatiquement par un `UIScreen` (dessin, événements, mémoire).

## 2. Constructeur

Pour créer un bouton, on utilise le constructeur suivant :

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

**Paramètres :**

* `x`, `y` (int16_t) : Coordonnées du coin supérieur gauche du bouton.
* `w`, `h` (int16_t) : Largeur et hauteur du bouton.
* `text` (const String&) : Le texte qui sera affiché au centre du bouton.
* `style` (const UIButtonStyle&) : Une structure définissant l'apparence du bouton (couleurs de fond, de texte, de bordure, etc.).
* `onPress` (std::function<void()>) : Une fonction (souvent une lambda) qui est appelée lorsque l'utilisateur appuie sur le bouton. Optionnel, peut être `nullptr`.
* `onRelease` (std::function<void()>) : Une fonction appelée lorsque l'utilisateur relâche son doigt du bouton. C'est l'équivalent d'un "clic" et l'action la plus couramment utilisée. Optionnel, peut être `nullptr`.

## 3. Méthodes Publiques Principales

* `void setText(const String& text)` : Change le texte affiché sur le bouton. N'oubliez pas d'appeler `draw()` après pour voir le changement.
* `void setEnabled(bool enabled)` : Active ou désactive le bouton. Un bouton désactivé ne répond pas aux événements tactiles et son apparence change (généralement grisé) pour indiquer son état.
* `bool isEnabled() const` : Retourne `true` si le bouton est activé.

## 4. Gestion des Événements (Callbacks)

La puissance du `UIButton` réside dans ses callbacks `onPress` et `onRelease`.

* **`onPress`** : Se déclenche dès que le doigt touche le bouton. Utile pour des retours visuels immédiats (comme changer la couleur du bouton).
* **`onRelease`** : Se déclenche lorsque le doigt est relâché *à l'intérieur* des limites du bouton. **C'est la méthode à privilégier pour les actions logiques** (changer d'écran, valider un formulaire, etc.) car elle permet à l'utilisateur d'annuler son action en glissant son doigt hors du bouton avant de le relâcher.

L'utilisation de fonctions lambda est la manière la plus simple de définir ces actions, notamment pour capturer le contexte de la classe (l'écran) dans laquelle le bouton est créé.

```cpp
// Exemple de lambda capturant 'this' pour accéder aux membres de l'écran
auto myButton = new UIButton(..., ..., nullptr, [this]() {
    // Ce code s'exécute au relâchement du bouton
    statusLabel->setText("Bouton cliqué !");
    screenManager.setActiveScreen(&otherScreen);
});
```

## 5. Style (`UIButtonStyle`)

L'apparence du bouton est définie par une structure `UIButtonStyle`. Vous devez en créer une instance et la passer au constructeur du bouton.

```cpp
// Fichier UIButtonStyle.h (exemple de structure)
struct UIButtonStyle {
    uint16_t fillColor = TFT_DARKGREY;
    uint16_t textColor = TFT_WHITE;
    uint16_t outlineColor = TFT_WHITE;
    uint16_t pressedFillColor = TFT_LIGHTGREY;
    uint16_t pressedTextColor = TFT_BLACK;
    // ... autres propriétés de style
};
```

## 6. Exemple d'Utilisation Complet

Voici un exemple complet tiré de la classe `HomeScreen` qui montre comment créer et utiliser un bouton pour changer d'écran.

```cpp
// Dans la méthode init() de votre classe qui hérite de UIScreen

// 1. Définir un style pour le bouton
UIButtonStyle settingsStyle;
settingsStyle.fillColor = TFT_BLUE;
settingsStyle.textColor = TFT_WHITE;
settingsStyle.outlineColor = TFT_CYAN;

// 2. Instancier le bouton avec une action au relâchement
auto settingsButton = new UIButton(
    tft.width() / 2 - 100, // x
    240,                   // y
    200,                   // w
    40,                    // h
    "Paramètres",          // texte
    settingsStyle,         // style
    nullptr,               // pas d'action onPress
    [this]() {             // action onRelease
        // Utilise le gestionnaire d'écrans global pour changer d'écran
        screenManager.setActiveScreen(&settingsScreen);
    }
);

// 3. Ajouter le bouton à l'écran pour qu'il soit géré automatiquement
addComponent(std::unique_ptr<UIComponent>(settingsButton));
```

Dans cet exemple, lorsque l'utilisateur clique sur le bouton "Paramètres", l'application navigue vers l'écran `settingsScreen`. La gestion de la mémoire est assurée par `addComponent` et `std::unique_ptr`.
