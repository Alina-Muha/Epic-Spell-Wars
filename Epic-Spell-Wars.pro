# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Epic-Spell-Wars

QT = core gui widgets
QT += network

HEADERS = \
   $$PWD/include/board.h \
   $$PWD/include/card.h \
   $$PWD/include/cards_functions.h \
   $$PWD/include/game.h \
   $$PWD/include/player.h \
   $$PWD/include/round.h \
   $$PWD/include/server.h \
   $$PWD/include/start_window.h

SOURCES = \
   $$PWD/.git/hooks/applypatch-msg.sample \
   $$PWD/.git/hooks/commit-msg.sample \
   $$PWD/.git/hooks/fsmonitor-watchman.sample \
   $$PWD/.git/hooks/post-update.sample \
   $$PWD/.git/hooks/pre-applypatch.sample \
   $$PWD/.git/hooks/pre-commit.sample \
   $$PWD/.git/hooks/pre-merge-commit.sample \
   $$PWD/.git/hooks/pre-push.sample \
   $$PWD/.git/hooks/pre-rebase.sample \
   $$PWD/.git/hooks/pre-receive.sample \
   $$PWD/.git/hooks/prepare-commit-msg.sample \
   $$PWD/.git/hooks/update.sample \
   $$PWD/.git/info/exclude \
   $$PWD/.git/logs/refs/heads/main \
   $$PWD/.git/logs/refs/heads/server \
   $$PWD/.git/logs/refs/remotes/origin/client-Alina-Muha \
   $$PWD/.git/logs/refs/remotes/origin/graphics-Alina-Muha \
   $$PWD/.git/logs/refs/remotes/origin/HEAD \
   $$PWD/.git/logs/refs/remotes/origin/main \
   $$PWD/.git/logs/refs/remotes/origin/server \
   $$PWD/.git/logs/HEAD \
   $$PWD/.git/objects/03/2d4989f3e65d675dad1b7d72ebe78e6385d353 \
   $$PWD/.git/objects/0c/310d61c6df7303a070f117996f40ca410a1230 \
   $$PWD/.git/objects/14/77a74f879b22cbab80e9815cb6f6b733a4271f \
   $$PWD/.git/objects/14/dfd5ebe01d96f2b1c86456c6f53d66135eb381 \
   $$PWD/.git/objects/1a/1bda17e3981b72260ea724a16d04681b853830 \
   $$PWD/.git/objects/1b/ad065d3932d7ff6a23527ccce6eaaa257e6865 \
   $$PWD/.git/objects/1e/959b86a1bee6c0d5392ee36d849c4fef98c40f \
   $$PWD/.git/objects/1e/d37e42f8ec6d5f894cd04e8777323170e07407 \
   $$PWD/.git/objects/23/a690b4743c7288a3ddcaa6abe7851dff693a05 \
   $$PWD/.git/objects/27/453c95066f8c50b28aff5db9419dd34ae2c92d \
   $$PWD/.git/objects/2b/f993f65084d6081d589df6180cc62e615a0494 \
   $$PWD/.git/objects/31/9290196352b69d19d74049f2793ba5d571cfd7 \
   $$PWD/.git/objects/3b/e66988ce821530e9062d525d8af404c9f5e102 \
   $$PWD/.git/objects/3d/dabb3dc4018a1b2aac22cf26f6658b632005ad \
   $$PWD/.git/objects/41/0bf9353e7789e16f69667a3a337649e1874a46 \
   $$PWD/.git/objects/48/a05323c2a80b7280218dfbc861fdce6255afbf \
   $$PWD/.git/objects/48/a4eca1e8b6d65a69914dc93eb6855fa73346a9 \
   $$PWD/.git/objects/4e/8fbd1a7bb75f830e9a02cedf03ecd86ef94ebc \
   $$PWD/.git/objects/51/e8db563a3d5f380d949c562c243bcfabb6bcb4 \
   $$PWD/.git/objects/57/b983da2645d2ba0dd999b4872d7d4dd1e233d4 \
   $$PWD/.git/objects/5c/13982add3d0fd5fe7a818c3049f8d96d4b8097 \
   $$PWD/.git/objects/5d/9b1fe00b44b6f7e2d211933c2cd4c64b08ac42 \
   $$PWD/.git/objects/60/000f977626042d4888f42972d4cc6acb6e9df7 \
   $$PWD/.git/objects/62/31a573643c821113cbdf7b8b16bd7a2fb3c32c \
   $$PWD/.git/objects/63/7f602d467ea6686dd7d44dea7103d209ec72b0 \
   $$PWD/.git/objects/64/ba8a0a1cd94f73a56112e3c3f38098adc991e9 \
   $$PWD/.git/objects/64/f65ac6d021024da2d69c7fd4731317948e8a55 \
   $$PWD/.git/objects/69/7825828aaa426ce055fe725b1b1448ab9517eb \
   $$PWD/.git/objects/6d/d653136b36ee89d8015db1b919e0abe35c5e86 \
   $$PWD/.git/objects/6f/1eb502732b22b94c3a1ca9f2aa96b279d1a016 \
   $$PWD/.git/objects/72/4effa5dc0f8b5dbe70f13a9ee7151cf924b5ec \
   $$PWD/.git/objects/72/83016f233ec728291ec790a0498eb4ed283afc \
   $$PWD/.git/objects/75/a3e4c323e73accea349a1afd50cd68072b768a \
   $$PWD/.git/objects/7b/8119c22d48b20eca3d871de44f8114e98d4ce7 \
   $$PWD/.git/objects/7d/b5a51fcb4284843cf60255ef80ea7798b55c4d \
   $$PWD/.git/objects/81/9aee0eb7667bc049078aa705506f4598c8ca94 \
   $$PWD/.git/objects/82/f39bdfe0d306ed63eb3348320965e15f5ea242 \
   $$PWD/.git/objects/84/079c2b5bbdbb3e66c04c284c0dc2d810d3320c \
   $$PWD/.git/objects/84/0fb67668f274f52eee999196292218367cf167 \
   $$PWD/.git/objects/8f/90d7ac2165eeee787f1f3b387fc29d819210fe \
   $$PWD/.git/objects/95/235880dabd2e5b1597220ffd13b66242c2fdac \
   $$PWD/.git/objects/97/24cb596a38b41ac244a81df14308a43e24af69 \
   $$PWD/.git/objects/9d/2a54518759c1fd67b15fd2027bfebc6c84c9b5 \
   $$PWD/.git/objects/9d/dae1bccdbf948528cf158c41420abf8520e9ad \
   $$PWD/.git/objects/a0/c811fd847bc660bdd08ef63f9ed4a49a208320 \
   $$PWD/.git/objects/a6/52752c86ddc0854318d3f6b9b8a5437cfc7918 \
   $$PWD/.git/objects/aa/e1b5adbb210a971cfbc7c265d791e677c67d37 \
   $$PWD/.git/objects/ae/5e7e0ab14648e9c9e10addd0314d2928cccedd \
   $$PWD/.git/objects/af/e288aec6a38ebd116dca69437fc690a8173049 \
   $$PWD/.git/objects/b9/88b15b77319224c852e86324cc65d199b63ae2 \
   $$PWD/.git/objects/b9/f395c08a72be37c5dd2eb5baa419ead90f7674 \
   $$PWD/.git/objects/ba/e2f98bc117f3885f507d9c67cff321c1edc2a6 \
   $$PWD/.git/objects/bb/e210e093ddbfb46a889aae87df8051f3f05e4e \
   $$PWD/.git/objects/bc/2f6e8646b890fd2c2e6ad9645b7f3da400d960 \
   $$PWD/.git/objects/bf/0e871a9191f93082498bd448cc6ac8bdf48ebd \
   $$PWD/.git/objects/c0/4461c832fac2cfbd9fd734c1e4d96e31f52a5f \
   $$PWD/.git/objects/d0/ef38b5a01523306cc652d389f93777f0d9167b \
   $$PWD/.git/objects/d9/544e4882720b57992ce4b46c39366d924d40e0 \
   $$PWD/.git/objects/dd/14fadfecd809511ccc90ed4207b5477a9ce85d \
   $$PWD/.git/objects/e4/1a5fd699f99159623769ab842d68a0e93b602f \
   $$PWD/.git/objects/e4/f51fd93b90fc977d90bd132c0c3275922fda4f \
   $$PWD/.git/objects/e7/08fe656fd55dac104d3bfb772c2ff0df44fa7e \
   $$PWD/.git/objects/ed/347de28a5f188e4780ad4f24d324560a5134be \
   $$PWD/.git/objects/f4/718e6026cc164e28952e87bbc23006b602838a \
   $$PWD/.git/objects/f6/cebd97160fd2a06d591a0e889a370e5f295d05 \
   $$PWD/.git/objects/f7/f31920fcb050b876b92ef83c5b19c4cede092a \
   $$PWD/.git/objects/fe/6f614f1272046980c467938a7bfad42240cd81 \
   $$PWD/.git/objects/fe/cfa820066388a32c9652371925299a28c7c7d5 \
   $$PWD/.git/objects/pack/pack-86049d2b3adccf5214306f988ac44a8096b9138b.idx \
   $$PWD/.git/objects/pack/pack-86049d2b3adccf5214306f988ac44a8096b9138b.pack \
   $$PWD/.git/refs/heads/main \
   $$PWD/.git/refs/heads/server \
   $$PWD/.git/refs/remotes/origin/client-Alina-Muha \
   $$PWD/.git/refs/remotes/origin/graphics-Alina-Muha \
   $$PWD/.git/refs/remotes/origin/HEAD \
   $$PWD/.git/refs/remotes/origin/main \
   $$PWD/.git/refs/remotes/origin/server \
   $$PWD/.git/COMMIT_EDITMSG \
   $$PWD/.git/config \
   $$PWD/.git/description \
   $$PWD/.git/FETCH_HEAD \
   $$PWD/.git/HEAD \
   $$PWD/.git/index \
   $$PWD/.git/ORIG_HEAD \
   $$PWD/.git/packed-refs \
   $$PWD/forms/board.ui \
   $$PWD/forms/start_window.ui \
   $$PWD/src/board.cpp \
   $$PWD/src/card.cpp \
   $$PWD/src/cards_functions.cpp \
   $$PWD/src/game.cpp \
   $$PWD/src/main.cpp \
   $$PWD/src/player.cpp \
   $$PWD/src/round.cpp \
   $$PWD/src/server.cpp \
   $$PWD/src/start_window.cpp \
   $$PWD/Epic-Spell-Wars.pro \
   $$PWD/Epic-Spell-Wars.pro.user

INCLUDEPATH = \
    $$PWD/include

#DEFINES = 

