ICP-Pacman
Autori: Běhal Tomáš xbehal02, Kontrík Jakub xkontr02
Použitie:
    Program je spustený pomocou make run
    Nasledovne je možné pohybovať sa po mape s pacmanom pomocou W-A-S-D alebo šípky.
    V ľavom hornom menu je možné si vybrať hernú mapu, poprípade replay.
    Po dokončení mapy alebo pri kolízií s duchom je možné replay uložiť klávesou “c”
    Replay sa ovláda pomocou tlačidiel poprípade klávesovými skratkami.

Implementácia
Štruktúra:
    backend.cpp: implementované výpočetné funkcie a práca s načítanou mapou
    gameover_scene.cpp:  vytvorenie gameover okna a nastavenie grafiky
    gamestate.cpp: riadiaca jednotka hry ktorá sa periodicky updatuje a volá backend na výpočet nových pozícii pre objekty
    ghost.cpp: reprezentácia ducha na mape
    key.cpp reprezentácia kľúča na mape
    main_scene.cpp: grafické znázornenie mapy a interaktívnych counteroch
    mainwindow.cpp: vytvorenie UI pre užívateľa, vytvorenie potrebných objektov
    map.cpp: uloženie mapy z textovej podoby
    map_object.cpp: objekty na mape
    pacman.cpp:  reprezentácia pacmana na mape
    replay.cpp: modul na spracovanie replayov

Splnená funkcionalita:
    implementované sú všetky základné požiadavky
    výber viacerých máp
    výber uložených replayov
    možnosť uložiť replay
    výber krokovania dopredu a dozadu v replay-i
    výber počiatočnej a koncovej pozície
    pohyb pomocou WASD a šípky
Nesplnené:
    pohyb myšou
    automatické prehratie replay-u
