# Stacja Meteo z Wykorzystaniem Technologii IoT - Embedded

## Opis Projektu

Projekt stacji meteo wykorzystującej technologie IoT do monitorowania i analizy warunków atmosferycznych. System zbiera dane z czujników i przesyła je do serwera, gdzie są one przechowywane w bazie danych i prezentowane za pomocą aplikacji webowej (znajdującej się w osobnym repozytorium).

## Cel Projektu

Głównym celem projektu jest stworzenie systemu umożliwiającego monitorowanie i analizę warunków atmosferycznych w sposób dokładny, niezawodny i łatwy w użyciu. Dzięki temu użytkownicy będą mogli uzyskać dostęp do aktualnych danych meteorologicznych na podstawie pomiarów przeprowadzanych przez stację meteo. Istotą projektu jest dostarczenie użytkownikom informacji na temat temperatury, wilgotności, natężenia światła itp., które są kluczowe dla wielu dziedzin życia, od codziennego planowania aktywności po profesjonalne aplikacje związane z monitorowaniem środowiska.

## Technologia

Projekt wykorzystuje następujące technologie:
- **Mikrokontroler STM32F303RE** - centralna jednostka zarządzająca.
- **Czujnik DS18B20** - pomiar temperatury.
- **Moduł WiFi ESP-01s** - komunikacja bezprzewodowa.
- **HTTP** - przesyłanie danych.

## Struktura Oprogramowania

Oprogramowanie składa się z trzech głównych modułów:
1. **Moduł Pomiarowy**: Zbieranie i przetwarzanie danych z czujników.
2. **Moduł Komunikacyjny**: Przesyłanie danych do serwera za pomocą ESP-01s i HTTP.
3. **Moduł Prezentacji**: Przechowywanie danych w bazie MySQL i prezentacja za pomocą aplikacji webowej (PHP) w osobnym repozytorium.

## Konfiguracja Projektu

### Schemat Połączeń Mikrokontrolera z Peryferiami

Mikrokontroler STM32F303RE jest podłączony przez kabel micro-AB USB.

#### Podłączenie czujnika DS18B20
- **Pin DQ**: Podłączony do pinu GPIO PC3 mikrokontrolera STM32F303RE.
- **Rezystor podciągający**: 4.7k ohm podłączony między linią danych czujnika a zasilaniem (3.3V).
- **Zasilanie (VDD) i masa (GND)**: Podłączone odpowiednio do napięcia zasilania (3.3V) i masy mikrokontrolera.

#### Podłączenie modułu WiFi ESP-01s
- **Zasilanie (VCC) i masa (GND)**: Podłączone do 3.3V i GND mikrokontrolera STM32F303RE.
- **Pin RX**: Podłączony do pinu PB10 (TX portu szeregowego UART2) mikrokontrolera.
- **Pin TX**: Podłączony do pinu PB11 (RX portu szeregowego UART2) mikrokontrolera.
- **Pin CH_PD**: Podłączony do napięcia zasilania (3.3V). Zalecane podłączenie do pinu GPIO w przyszłości.
- **Pin RESET**: Podłączony do pinu GPIO PC4, umożliwiający reset modułu WiFi z poziomu programu.
