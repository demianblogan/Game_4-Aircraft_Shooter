[![en](https://img.shields.io/badge/Language-English-red.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/blob/main/README.md)
[![ru](https://img.shields.io/badge/Language-Russian-blue.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/blob/main/README.ru.md)
[![ua](https://img.shields.io/badge/Language-Ukrainian-green.svg)](https://github.com/demianblogan/Game_4-Aircraft_Shooter/blob/main/README.ua.md)

# **Обзор**<br />
Это моя 3я игра в моем портфолио. Этот проект написан на C++ с использованием SFML. Это авиационный шутер с камерой сверху вниз. Вы управляете самолетом с помощью клавиш WASD (по умолчанию). Вы можете стрелять пулями и ракетами (клавиши ПРОБЕЛ и М по умолчанию). Пули летят прямо вверх, ракеты пытаются найти самолет противника и лететь к нему. У каждого самолета есть очки здоровья (даже у вас). Ваш самолет имеет ограниченное количество ракет. Есть два типа самолетов противника: первый может стрелять пулями, а второй просто летает. Враги появляются в верхней части окна и летят вниз. Если вы столкнетесь с одним из самолетов противника, он будет уничтожен, но вы получите удар. Ваша цель — достичь конца уровня (в конце вы увидите финишную черту). Если ваши очки здоровья упадут ниже 0, вы проиграете игру. В игре есть несколько состояний - состояние титульного экрана (первое, которое вы увидите), состояние главного меню (с пунктами «Играть», «Настройки» и «Выход»), состояние меню настроек (где вы можете привязать клавиши с определенным действиям), состояние игры (где вы на самом деле играете) и состояние паузы (нажмите ESCAPE, когда находитесь в состоянии игры). Когда враги уничтожены, из них могут выпасть предметы улучшений с вероятностью 33%.

![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/7861bf1a-6aed-4984-b622-1c11ea5dc7c2)

## **Управление:**<br />
Стрелка влево -> Переместить самолет влево<br />
Стрелка вправо -> Переместить самолет вправо<br />
Стрелка вверх -> Переместить самолет вверх<br />
Стрелка вниз -> Переместить самолет вниз<br />
Проблел -> Стрелять пулями<br />
M -> Выпустить ракету<br />
Ентер -> Выбрать пункт меню<br />
Ескейп -> Поставить игру на паузу<br />

## **Как создать и скомпилировать этот проект в Visual Studio?**<br />
1. Загрузите этот репозиторий в виде файла .zip и распакуйте его:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/536db98f-b1bd-40c9-983d-b31e1f2e235d)

2. Создайте пустой проект C++ в Visual Studio:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/f2da9908-e3c8-4840-bc92-62e61c981350)

3. Откройте папку проекта в проводнике и переместите в нее все файлы из архива:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/b01abf94-3866-45ca-86f6-a391e0669594)

4. Теперь вам нужно включить эти файлы в свой проект. Сначала, чтобы сделать все эти файлы видимыми в вашем проекте, нажмите кнопку «Show All Files» в Solution Explorer. После этого выделите их, ПКМ по ним и нажмите «Include in Project»:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/cc97cdb1-4229-4360-a4e2-585e5eee5149)

5. В свойствах проекта сначала установите местоположение бинарных файлов:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/eb8f3659-4cc5-4ca4-af5e-f0b2745aeec8)

6. Подключите библиотеку SFML к проекту. Начнем с папки «include». Перейдите на вкладку «C/C++», найдите «Additional Include Directories», нажмите стрелку справа и нажмите «<Edit...>»:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/cb80df18-c8eb-45de-9b49-aba7b8734c6e)

7. Теперь сделайте то же самое с папкой «lib»: перейдите на вкладку «Linker», найдите «Additional Library Directories», нажмите стрелку справа и нажмите «<Edit...>»:<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/dbaa2397-b082-433f-94de-e9ceeb1836f2)

8. Почти готово. Нам нужно только добавить в наш проект файлы .dll. Сохраните изменения, нажав кнопку «Apply» внизу свойств проекта, измените конфигурацию на «Debug», перейдите на вкладку «Linker» -> «Input», найдите «Additional Dependencies», щелкните стрелку справа. и нажмите «<Edit...>».<br />
В новом окне напишите следующие строки:<br />
sfml-system-d.lib<br />
sfml-window-d.lib<br />
sfml-audio-d.lib<br />
sfml-graphics-d.lib<br />
sfml-network-d.lib<br />
и нажмите кнопку «ОК».<br />
Сделайте то же самое с конфигурацией Release, но удалите префиксы "-d":<br />
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/9d14f17b-bbf7-4705-81c1-8ef652ce94ea)
![image](https://github.com/demianblogan/Game_4-Aircraft_Shooter/assets/105989117/e87c4240-74da-4121-a74b-ba35a7bbc186)

9. Теперь можно скомпилировать проект.
