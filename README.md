# Tetris C++ Spill

## Beskrivelse

Dette prosjektet er en implementering av det klassiske Tetris-spillet i C++ ved hjelp av Threepp for
3D-grafikk og rendering.

## Funksjoner

- **3D Grafikk**: Spillet bruker threepp-biblioteket for å generere 3D-grafikk og visualisere Tetris-spillet.

- **Tetris Logikk**: Spillet inkluderer Tetris-logikken, der spillbrikker faller ned og kan roteres og flyttes av
  spilleren.

- **Mål 60 FPS**: Spillet sikter på å opprettholde en jevn ytelse ved å målrette mot 60 bilder per sekund.

- **Enhetstester**: Spillet bruker Catch2 som et enhetstestrammeverk for å sikre påliteligheten til koden.

- **Continuous Integration**: Continuous Integration (CI) er implementert for automatisk bygging og testing av
  prosjektet.

## Avhengigheter

- [threepp](https://github.com/markaren/threepp): Trejs-biblioteket brukes til 3D-grafikk og rendering.

- [Catch2](https://github.com/catchorg/Catch2): Catch2 brukes til enhetstester (valgfritt, krever aktivering).

## Installasjon

For å kompilere og kjøre spillet, må du ha CMake og de nødvendige avhengighetene installert.

1. Klon dette repositoryet:
   git clone https://github.com/Dannor00/Eksamen_2023.git
   cd Eksamen_2023


2. Opprett en byggmappe:
   mkdir build
   cd build


3. Generer CMake-prosjektet:
   cmake ..

4. Kompilér spillet:
   make


5. Kjør spillet:
   ./Tetris

### Oppsett av threepp vcpkg-test

Hvis du vil inkludere threepp vcpkg-test i prosjektet, følg disse trinnene:

1. Erstatt `baseline`-verdien i vcpkg-configuration.json med en commit fra den tilpassede vcpkg-registret som inneholder
   threepp-porten.

2. Legg til følgende CMake-variabler for avhengighetsoppløsning (pass på at du erstatter `[path to vcpkg]` med banen til
   vcpkg):

-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake

med MinGW mp du spesifisere vcpkg:

-DVCPKG_TARGET_TRIPLET=x64-mingw-[static|dynamic]  # choose either `static` or `dynamic`.
-DVCPKG_HOST_TRIPLET=x64-mingw-[static|dynamic]    # <-- needed only if MSVC cannot be found.

## Spillkontroll

- **A- og D**: Flytt brikken til venstre og høyre.
- **W**: Roter brikken.
- **S**: La brikken falle raskere.


## Enhetstester

Hvis du vil kjøre enhetstestene (krever at Catch2 er aktivert), gjør følgende:

1. Aktiver enhetstest under CMake-konfigurasjonen ved å angi `-DTERRIS_BUILD_TESTS=ON`.

2. Rekompiler prosjektet.

3. Kjør enhetstestene ved å kjøre:
   allTestes

Happy gaming!




