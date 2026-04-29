# Flop

### Pour regarder les mises à jour les plus récentes, veuillez regarder la branche [upcoming](https%3A%2F%2Fgithub.com%2Fflop-gg%2Fflop-sdk%2Ftree%2Fupcoming).

![GitHub Tag](https://img.shields.io/github/v/tag/flop-gg/flop-sdk?label=version&color=green) ![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/m/flop-gg/flop-sdk/upcoming?label=commit%20activity%20(upcoming)&link=https%3A%2F%2Fgithub.com%2Fflop-gg%2Fflop-sdk%2Ftree%2Fupcoming) ![GitHub last commit](https://img.shields.io/github/last-commit/flop-gg/flop-sdk)

Flop est un jeu multijoueur basé sur le moteur [Source](https://developer.valvesoftware.com/wiki/Source), sous le [Source SDK 2013](https://developer.valvesoftware.com/wiki/Setting_up_Source_SDK_Base_2013_Multiplayer). Le jeu mélange des éléments Call of Duty, Counter-Strike, etc.
Ce jeu est juste un petit projet entre moi et mes amis pour avoir quelque chose à jouer en privé, veuillez noter qu'il est donc possible que le code source devient privé à un moment ou l'autre pour cette raison.
En attendant, au moins jusqu'à la dernière version beta, le jeu est ouvert. (Si vous êtes quelqu'un que je connais, je peux quand-même vous donner le code source).

## Sommaire
1. Construction du jeu
2. Codes utilisés
3. Licence

## Construction du jeu
Pour construire le jeu, veuillez suivre les instructions de Valve [ici](https://github.com/valvesoftware/source-sdk-2013?tab=readme-ov-file#build-instructions). Veuillez noter que le code Linux n'est pas testé, compilez-donc à vous risques et périls.

Des nouveaux scripts .bat sont fournis afin que ce soit plus facile pour programmer le jeu. Ces scripts sont:
- `create_flop_basic.bat`
  + Contient *uniquement* les .dll du jeu (`client.dll`, `server.dll`, etc)
  + Créé plutôt pour une lisibilité plus facile sur Visual Studio.
- `create_flop_full.bat`
  + Contient les .dll du jeu (`client.dll`, `server.dll`, etc)
  + Contient le launcher (`flop_win64.exe`).
  + Créé pour faciliter l'automatisation GitHub Actions.

## Codes utilisés
- https://developer.valvesoftware.com/wiki/Override_GameUI
- https://developer.valvesoftware.com/wiki/Adding_an_HTML_Main_Menu
- https://developer.valvesoftware.com/wiki/Hand_Viewmodels

Veuillez noter que j'ai également utilisé des intelligences artificelles comme [Claude](claude.ai) afin de m'aider à faire des recherches. Je suis encore en scolarité et je n'ai pas le temps pour regarder tout le code de ce moteur. J'essaye quand-même de ne pas faire du copier-coller de A à Z et de me renseigner sur le code donné, j'essaye néanmoins de faire la plupart du code par moi-même (pas de vibe coding).

## Licence
Le code du jeu est licencé sous la [SOURCE 1 SDK LICENSE](LICENSE), inclus sur tous les projets Source Engine. Si vous voulez prendre quelque chose de ce code, vous y êtes donc libre.
