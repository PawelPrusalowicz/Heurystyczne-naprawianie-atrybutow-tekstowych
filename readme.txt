ZPR - szkielet projektu biblioteki

temat: Heurystyczne naprawianie atrybutów tekstowych
zespół: Gabriela Lewandowska, Paweł Prusałowicz

wymagane:
-python
-boost.python
-SCons (w pliku SConstruct należy ustawić ścieżki do pythona oraz boost.python)

proces kompilacji (Linux):
po odnalezieniu w terminalu folderu, w którym znajdują się pliki, wpisać:
scons 

następnie test bibliteki można uruchomić (z katalogu głównego) poprzez:
python3 -m test.test_text_correction

aby uruchomić jesty jednostkowe (z katalogu głównego):
bash run_unit_test.sh 

aby uruchomić test szybkości algorytmów (z katalogu głównego):
bash run_speed_test.sh