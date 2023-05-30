= 基礎知識

アドオンを作り始める前に、基礎知識を習得します。
基礎知識と言ってもPythonの書き方といった技術的な要素ではなく、
画面の見方やツールの扱い方の紹介がメインです。

== System Consoleの表示

アドオンのインストールや実行でエラーが発生すると、関連するメッセージが出力されます。
ポップアップウィンドウやScriptingタブのInfoエリアで確認できるものもありますが、
System Consoleが使えると原因究明に役立ちます。
小規模なアドオン開発ではあまり使わないかもしれませんが、
そういったものがあるということは頭の片隅に置いておくとよいでしょう。

System ConsoleはWindows版であればBlenderのWindow → Toggle System Consoleから開くことができます。

//image[console][System Consoleの表示]{
//}

macOS版では前述のメニューが存在しません。Terminal.app@<fn>{terminal}で次のコマンド@<fn>{command}を入力し、
EnterをクリックするとBlenderが起動し、Terminal.app上にSystem Consoleへの出力が表示されます。
この方法で呼び出したBlenderを終了させるときは通常通りウィンドウを閉じてください。

//list[path][][text]{
/Applications/Blender.app/Contents/MacOS/Blender
//}

//image[terminal][Terminal.appでBlenderを起動したときの表示]{
//}

//footnote[terminal][ プリインストールされており、 @<code>{Applications/Utilities} 内に格納されている。 ]
//footnote[command][ BlenderをApplicationsフォルダにインストールしている場合のコマンド ]

== 画面の説明

続いて、Scriptingタブについて説明します。
モデリングなどで使用することはほぼありませんが、
アドオン開発では頻繁に操作することになります。

Scriptingタブの画面配置は、デフォルトで次のエリアが含まれます。

  1. @<code>{3D Viewport}: 普段モデリングで使用する画面と同一です
  2. @<code>{Python Console}: Pythonスクリプトを実行できます
  3. @<code>{Info}: Blender上で実行された処理などの情報が出力されます
  4. @<code>{Text Editor}: Pythonスクリプトの作成・編集などができます

//image[window_bl][Scriptingタブの画面配置]{
//}

== スクリプトの実行

早速、Python Consoleを使用してみます。
Python ConsoleではBlender自体や各データの確認・操作ができます。
開発においては状態の確認や簡単な動作テストをするときに便利です。

それでは、ScriptingタブのPython Consoleに次のスクリプトを入力し、Enterキーをクリックしてください。

//list[version][][python]{
print("Blenderのバージョン:", bpy.app.version_string)
//}

//image[output][スクリプトの実行結果]{
//}

入力したコマンドの下に、 @<code>{Blenderのバージョン: <読者のBlender Version>} と表示されています。
"print()"は括弧内のオブジェクト@<fn>{object}をテキストとして出力する関数@<fn>{function}です。
先ほどのprint関数には括弧の中にカンマで区切られた2かたまりの文字列がありました。
1つ目の@<code>{"Blenderのバージョン:"} は文字列データです。
Pythonにおいて、文字列は @<code>{"} か @<code>{'} で囲まれた形で表現されます。
2つ目の@<code>{bpy.app.version_string}はBlender Python APIを使用して、Blenderのバージョン情報を取得しています。

ここで用語説明を挟みます。先ほどの説明に出てきた"オブジェクト"とはPythonで扱うデータをさします。
Blender Python APIとは、Blenderのデータや機能にアクセスするためのものです。
先ほどのコードでは、Blenderのバージョン情報を@<code>{bpy.app.version_string}というコードで呼び出していました。
アドオンによる設定項目や3Dオブジェクトへの操作も、Blender Python APIを使用して行います。
抽象的なものですので慣れるまではよくわからないかもしれませんが、作業を進めるうちに理解できてくると思います。
完全に納得してから進めたい、という方は注釈にある公式ドキュメントが役立ちます。

次はPythonでCubeオブジェクトを作成し、操作してみます。
3D Viewport上にオブジェクトがある場合は削除しておきましょう。
準備ができたら、次のコマンドをPython Consoleで実行してください。
なお、入力は1行ずつ行い、@<code>{#}で始まる行は飛ばしてください。

//list[cube][][python]{
# Cubeオブジェクトを作成
bpy.ops.mesh.primitive_cube_add()

# 作成したオブジェクトを変数 "cube" に代入
cube = bpy.context.object

# オブジェクトの位置を変更
cube.location = (2, 0, 0)

# オブジェクトのスケールを変更
cube.scale = (2, 2, 2)

# オブジェクトをZ軸周りに90度(π/4)回転
cube.rotation_euler = (0, 0, 0.785)

# オブジェクトを削除
bpy.ops.object.delete()
//}

//image[script][実行したスクリプト]{
//}

//image[cube][スクリプトでスケール・角度を変更したCubeオブジェクト]{
//}

最初の例よりもアドオン開発に近づいてきた実感が得られたのではないでしょうか。
しかし、行数が増えてくると実行する手間が無視できなくなってきます。
次は、あらかじめ処理を定義して実行する方法を試します。

処理の定義はText Editorエリアを使用します。
エリア上部の"+ New"ボタンをクリックし、先ほどのスクリプトを貼り付けます。
貼り付けをするとき、@<code>{#} を含めた状態で問題ありません。
@<code>{#}で始まる行は"コメント"と呼ばれ、@<code>{#}以降は実行時に無視されます。
コメントは後からコードを読み返すためにそのコードが何をしているのかという説明や、
ToDo（例：@<code>{# ToDo: ~~~を追加}）を残しておくために使用されます。

貼り付け後、Text Editorエリア上部の実行ボタン（三角形が描かれたボタン）をクリックし、
スクリプトを実行してください。
実行すると、図3.2.4のInfoエリア（左下）にあるエラーが表示されます。

//image[result_1][実行結果]{
//}

エラー部分には次のように記載されています。

//list[error][][shell]{
Python: Traceback (most recent call last):
  File "/Text", line 2, in <module>
NameError: name 'bpy' is not defined
//}

2行目、3行目の情報から、"Textファイル（作成したスクリプト）の2行目でエラー"、 "bpyが未定義"と読み取れます。
@<code>{bpy}とはBlenderにアクセスする際に使用していましたね。
エラーの説明は章末のコラムで紹介することにして、今は作業を進めます。
スクリプトの先頭に空行を追加し、@<code>{import bpy}と入力し、もう一度スクリプトを実行してください。

//image[result_2][実行結果]{
//}

Infoエリアに3行表示が増えました。うまく動いたような気もしますが、3D Viewportに何も表示がなく実際どうだったのか判断できません。
各行の間に処理を一時停止して処理の進行を見たいところですが、Text Editor上で一時停止の処理をするとBlenderからの応答がなくなるため
一番最後のオブジェクト削除処理をコメントアウト@<fn>{comment_out}して再実行してみます。

//list[comment_out][][diff]{
# オブジェクトを削除
bpy.ops.object.delete()

↓

# オブジェクトを削除
# bpy.ops.object.delete()
//}

//image[result_3][実行結果]{
//}

スクリプトによってCubeを生成・操作できたようです。
このようにして、PythonスクリプトでBlenderを操作できることがわかりました。
次の章から、実際にアドオンを作成してみます。

//footnote[object][ https://docs.python.org/3/reference/datamodel.html#objects-values-and-types ]
//footnote[function][ https://docs.python.org/3/glossary.html#term-function ]
//footnote[comment_out][ 行頭に@<code>{#}を付け、処理を無効化することを"コメントアウト"と呼びます ]

== まとめ

本章では、アドオン制作の基礎となる要素を取り上げました。
Python ConsoleやText Editorを使用するとBlenderを操作し
目的の処理をさせることができます。
便利な処理はプロジェクトを問わず使用したいですし、
作業画面からすぐに呼び出せた方が便利です。
それを実現するのが、アドオンということになります。

次の章では、いよいよアドオンの作成を開始します。

===[column] NameErrorとは？

本章で遭遇したエラーに、@<code>{NameError: name 'bpy' is not defined}がありました。
このコラムでは、エラーの意味とPython Consoleで同じエラーが発生しなかった理由を説明します。

まず、エラーの意味ですが"@<code>{bpy}という名前のオブジェクトが存在しない"ということを伝えています。
例えば、定義していない変数や関数を呼び出したとき、打ち間違いにより定義と異なる名前を指定したときなどにこのエラーが発生します。

Blender Python APIを使用するには、@<code>{bpy}というモジュール@<fn>{module}を読み込む必要があります。
モジュールを読み込む処理が @<code>{import bpy}であり、その一行を追加したことでエラーが解消したというわけです。

では、Python Consoleでモジュールを読み込まなくてもBlender Python APIが使用できた理由は何でしょうか。
Python Consoleに最初から表示されている文字列の中に、次のような記載があります。

//list[][][text]{
Builtin Modules:       bpy, bpy.data, ...(※紙面の都合により省略)
//}

この行が意味することは、記載されているモジュールはすでにロード済みであるということです。
手動でロードしなくてもBlenderが起動した時点でbpyモジュールがロードされていたため、
モジュールの読み込み処理を書かなくてもエラーが発生しなかったのです。

===[/column]

//footnote[module][ データや処理を定義し、まとめたもの。 https://docs.python.org/3/tutorial/modules.html ]
