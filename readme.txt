ZPR - szkielet projektu biblioteki

temat: Heurystyczne naprawianie atrybutów tekstowych
zespół: Gabriela Lewandowska, Paweł Prusałowicz

wymagane:
-python
-boost.python
-SCons (w pliku SConstruct należy ustawić ścieżki do pythona oraz boost.python)

proces kompilacji (Linux):
po odnalezieniu w terminalu folderu, w którym znajdują się pliki, wpisać:
scons -boost_python

następnie można uruchomić test poprzez:
python3 -m test.text_correction

uruchomienie testu jednostkowego:
python3 -m test.test_text_correction