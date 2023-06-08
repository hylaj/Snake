# Snake
Klasyczna gra Snake napisana za pomocą języka C++ oraz biblioteki Allegro 5. Rozgrywka polega na kontrolowaniu stale poruszającego się snake’a i zdobywaniu jedzenia, które powoduje wydłużanie się jego ciała, co znacznie utrudnia grę. Snake ginie, kiedy uderzy własną głową w swoje ciało lub w otaczające planszę ściany. Uwaga: nie ma możliwości zatrzymania snake’a w trakcie rozgrywki.

## Sterowanie

  -	  ←/→ /↑/  ↓   - sterowanie ciałem snake’a (zakres ruchów: lewo/prawo/góra/dół)
  
  -   ENTER  -  start rozgrywki (lub reset rozgrywki zaraz po przegranej)
  
  -   ESC  -  wyjście z gry

## Rozgrywka

  -  **Pierwsze uruchomienie** – ukazuje się ekran startowy. Aby rozpocząć rozgrywkę należy wcisnąć klawisz ENTER – snake rusza od razu.

![Start](https://github.com/hylaj/Snake/assets/135766871/9bde8401-80dc-42ac-a089-71d9f1a9f28b)


  -  **Rozgrywka** polega na sterowaniu ciałem węża za pomocą klawiszy ←/→ /↑/  ↓ . Snake porusza się cały czas z taką samą prędkością i nie ma      możliwości zatrzymania go. Początkowo jego ciało składa się z 3 elementów. Kiedy głowa snake’a zetknie się z pokarmem, graczowi przyznawany      jest 1 punkt, a ciało snake’a wydłuża się o 1 element. 

![Game](https://github.com/hylaj/Snake/assets/135766871/7e6ddbc6-4bb0-4946-98cd-20c48d5a30f6)


  -  **Koniec gry** - Gra się kończy, kiedy snake uderzy głową w ściany planszy bądź w część własnego ciała. Jeśli gracz osiągnie wyższy wynik niż     wszystkie do tej pory, zostanie on zaktualizowany i zapisany w pliku BestScore.txt oraz wyświetlony na ekranie.

![Game over2](https://github.com/hylaj/Snake/assets/135766871/8a72a58b-de7e-4b18-a934-b00546863d03)



  -   **Restart** – po krótkiej chwili snake jest przywracany do wartości początkowych. Gracz wciskając ENTER ma możliwość rozpoczęcia nowej           rozgrywki. 

![Game over](https://github.com/hylaj/Snake/assets/135766871/7b973826-cfcf-425b-ac7a-12adcd64646d)



## Algorytm 

  -	**Add_Body** - Ciało snake’a jest listą dwukierunkową, której elementy składają się ze współrzędnych x i y, kierunku oraz wskaźników do poprzedniej i następnej części ciała. Kiedy wąż zje pokarm, nowy element wstawiany jest na początek listy i staje się nową głową snake’a.

![Add_Body](https://github.com/hylaj/Snake/assets/135766871/ea1285a8-8f25-4df4-b60e-4f5ee44b55d8)


  -	Za poruszanie się snake’a odpowiada funkcja **Move_Snake**, która każdemu elementowi ciała przypisuje współrzędne elementu poprzedzającego. Sterowanie odbywa się głową poprzez dodanie lub odjęcie odpowiedniej ilości pikseli do/od aktualnych współrzędnych, w zależności od obranego przez użytkownika kierunku.

![Move_Snake](https://github.com/hylaj/Snake/assets/135766871/232e1363-4f70-49c7-85a1-b0d75c071fcd)


  -	Funkcja **Generate_Apple** jest wywoływana, kiedy snake zje pokarm, dlatego na samym początku wywołuje ona funkcję Add_Body, która wstawi nową część ciała snake’a. Następnie generuje nowy pokarm, losując wartości jego współrzędnych i kolejno sprawdza, czy wylosowane współrzędne nie kolidują ze współrzędnymi każdego elementu ciała snake’a (lub znajdują się za blisko). Jeśli kolizja wystąpiła, ponawiamy losowanie współrzędnych pokarmu i ponownie sprawdzamy, czy nie ma kolizji. Po wylosowaniu poprawnych współrzędnych następuje losowanie rodzaju pokarmu, za które odpowiada funkcja Apple_lottery.

![Generate_Apple](https://github.com/hylaj/Snake/assets/135766871/07ba215f-ef27-4171-9983-475c894386dd)


## Instrukcja instalacji

Gra była tworzona i testowana na systemie Windows 11. 
Do skompilowania gry wymagana jest instalacja **Visual Studio** (https://visualstudio.microsoft.com/pl/downloads/) oraz biblioteki Allegro 5 w wersji **Allegro 5.2.8**. Należy pobrać archiwum .zip zawierający wszystkie pliki projektu niezbędne do uruchomienia gry, otworzyć plik **.sln**, a następnie zainstalować paczkę Allegro wg tutorialu: https://gamefromscratch.com/allegro-tutorial-series-part-1-getting-started/ . Należy dodać następujące addons: *Image, Font, Truetype Font*.
