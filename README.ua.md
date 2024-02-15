[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/blob/main/README.md)
[![ru](https://img.shields.io/badge/Language-Russian-blue.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/blob/main/README.ru.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/blob/main/README.ua.md)

# **Огляд**<br />
Це моя 3-я гра в моєму портфоліо. Цей проект написано на C++ із використанням SFML. Це авіаційний шутер із камерою зверху вниз. Ви керуєте літаком за допомогою WASD (за замовчуванням). Ви можете стріляти кулями та ракетами (клавіші ПРОБІЛ та М за замовчуванням). Кулі летять прямо вгору, ракети намагаються знайти літак противника та летіти до нього. Кожен літак має очки здоров'я (навіть у вас). Ваш літак має обмежену кількість ракет. Є два типи літаків противника: перший може стріляти кулями, а другий просто літає. Вороги з'являються у верхній частині вікна і летять униз. Якщо ви зіткнетеся з одним із літаків противника, він буде знищений, але ви отримаєте удар. Ваша мета – досягти кінця рівня (наприкінці ви побачите фінішну межу). Якщо ваші очки здоров'я впадуть нижче 0, ви програєте гру. У грі є кілька станів - стан титульного екрану (перший, яке ви побачите), стан головного меню (з пунктами "Грати", "Налаштування" та "Вихід"), стан меню налаштувань (де ви можете прив'язати клавіші до певних дій), стан гри (де ви дійсно граєте) і стан паузи (натисніть ESCAPE, коли перебуваєте в стані гри). Коли ворогів знищено, з них можуть випасти предмети поліпшень із ймовірністю 33%.

![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/7861bf1a-6aed-4984-b622-1c11ea5dc7c2)

## **Керування:**<br />
Стрілка влево -> Перемістити літак вліво<br />
Стрілка вправо -> Перемістити літак вправо<br />
Стрілка вверх -> Перемістити літак вверх<br />
Стрілка вниз -> Перемістити літак вниз<br />
Пробіл -> Стріляти кулями<br />
M -> Випустити ракету<br />
Ентер -> Вибрати пункт меню<br />
Ескейп -> Поставити гру на паузу<br />

## **Як створити та скомпілювати цей проект у Visual Studio?**<br />
1. Завантажте цей репозиторій у вигляді .zip і розпакуйте його:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/536db98f-b1bd-40c9-983d-b31e1f2e235d)

2. Створіть порожній проект C++ у Visual Studio:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/f2da9908-e3c8-4840-bc92-62e61c981350)

3. Відкрийте папку проекту у провіднику та перемістіть у неї всі файли з архіву:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/b01abf94-3866-45ca-86f6-a391e0669594)

4. Тепер вам потрібно включити ці файли до свого проекту. Спочатку, щоб зробити всі ці файли видимими у вашому проекті, натисніть кнопку "Show All Files" у Solution Explorer. Після цього виділіть їх, ПКМ за ними та натисніть «Include in Project»:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/cc97cdb1-4229-4360-a4e2-585e5eee5149)

5. У властивостях проекту спочатку встановіть розташування бінарних файлів:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/eb8f3659-4cc5-4ca4-af5e-f0b2745aeec8)

6. Підключіть бібліотеку SFML до проекту. Почнемо з папки "include". Перейдіть на вкладку C/C++, знайдіть Additional Include Directories, натисніть стрілку праворуч і натисніть <Edit...>:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/cb80df18-c8eb-45de-9b49-aba7b8734c6e)

7. Тепер зробіть те саме з папкою lib: перейдіть на вкладку Linker, знайдіть Additional Library Directories, натисніть стрілку праворуч і натисніть <Edit...>:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/dbaa2397-b082-433f-94de-e9ceeb1836f2)

8. Майже готово. Нам потрібно лише додати до нашого проекту файли .dll. Збережіть зміни, натиснувши кнопку "Apply" внизу властивостей проекту, змініть конфігурацію на "Debug", перейдіть на вкладку "Linker" -> "Input", знайдіть "Additional Dependencies", клацніть правою стрілкою. та натисніть «<Edit...>».<br />
У новому вікні напишіть наступні рядки:<br />
sfml-system-d.lib<br />
sfml-window-d.lib<br />
sfml-audio-d.lib<br />
sfml-graphics-d.lib<br />
sfml-network-d.lib<br />
та натисніть кнопку «ОК».<br />
Зробіть те саме з конфігурацією Release, але видаліть префікси "-d":<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/9d14f17b-bbf7-4705-81c1-8ef652ce94ea)
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/e87c4240-74da-4121-a74b-ba35a7bbc186)

9. Тепер можна скомпілювати проект.
