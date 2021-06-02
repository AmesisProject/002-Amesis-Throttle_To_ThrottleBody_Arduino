# 002-Amesis-Throttle_To_ThrottleBody_Arduino
YouTube : https://youtu.be/p9pYdOgZvkU

VE
Order a motorized throttle body for gasoline engines with an electronic pedal and an arduino
Development of the 1st functional version so that the pedal (VAG VR5 170cv AQN, probably similar to other pedals of the VAG group including the VR6, 1.8T, or even any other potentiometer)

Amesis_throttle.ino
Ok functional returns the value 0 to 100% of the pedal to the console of the Arduino IDE

Youtube: https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?sub_confirmation=1
GitHub: https://github.com/AmesisProject
Discord: https://discord.gg/vRAybmd3hk
FaceBook: https://www.facebook.com/amesis.pro.5
Instagram: https://www.instagram.com/?hl=fr
Amesisproject@gmail.com
  
  OpenSource CC-BY-NC-SA license
  not salable, editable by citing the owner AmesisProject with the links above
  Based on the arduino AnalogInOutSerial example
  
Beta_V1.1_Amesis-Throttle_To_ThrottleBody_Arduino
Version: Beta V1.1 05/30/2021
YouTube: https://youtu.be/v8cY9vEKRA4
Problem to be resolved: The butterfly oscillates very slightly (not visible to the eye but we can hear it) on the previous version it oscillated too much, this was due to the serial.begin too slow. I completely deleted it for the functional V Beta.
To add: -The PID library (to weaken the oscillation)
            -Find a way to return the throttle position value to the speeduio because currently it is returned to the arduino of the Thottle_To_ThrottleBody project and not to the arduino of the Speeduino
             this problem could be solved simply with the second potentiometer integrated in the motorized throttle not used until now in the project.
             this solution requires 2 arduino, one for the butterfly control project with the pedal and one with the Speeduino

Please forward on github any modification to the improvement of the code and report any problem in the "Issues" tab of the project on GitHub

VF
Commander un boitier papillon motorisé des moteur essence avec une pédale électronique et un arduino 
Mise au point de la 1er version fonctionnelle pour que la pédale (VAG VR5 170cv AQN, surement similaire a d'autre pédale du groupe VAG notamment le VR6, 1.8T, ou même n'importe quel autre potensiometre )

Amesis_throttle.ino 
Ok fonctionnel renvoie la valeur 0 à 100 % de la pédale à la console de l'IDE Arduino

Youtube   : https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?sub_confirmation=1
GitHub    : https://github.com/AmesisProject
Discord   : https://discord.gg/vRAybmd3hk
FaceBook  : https://www.facebook.com/amesis.pro.5
Instagram : https://www.instagram.com/?hl=fr
Amesisproject@gmail.com
  
  licence OpenSource CC-BY-NC-SA 
  non commercialisable, modifiable en citant le propriétaire AmesisProject avec les liens ci dessus
  Sur base de l'exemple arduino AnalogInOutSerial
  
Beta_V1.1_Amesis-Throttle_To_ThrottleBody_Arduino 
Version     : Beta V1.1 30/05/2021
YouTube     : https://youtu.be/v8cY9vEKRA4
Problème à régler : La papillon oscille très légèrement (non perseptible à l'oeil mais on l'entend) sur la version precédante il oscillé beaucoup trop, cela été du au serial.begin trop lent. Je l'ai carrement supprimé pour la V Beta fonctionnelle.
A ajouter : -La librairie des PID (pour affaiblir l'oscillation)
            -Trouver le moyen de renvoyer la valeur de position papillon au speeduio car actuellement elle est renvoyé a l'arduino du projet Thottle_To_ThrottleBody et non a l'arduino du Speeduino
             se problème pourrait être réglé simplement avec le second potentiomettre integré au papillon motorisé inutilisé jusqu'a présent dans le projet.
             cette solution impose 2 arduino, un pour le projet de commande papillon avec la pedale et un avec le Speeduino

Merci de faire suivre sur github toute modification au amélioration du code et de faire remonter les eventuel problème dans l'onglet "Issues" du projet sur GitHub
