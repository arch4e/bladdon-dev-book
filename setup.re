= 環境構築

この章では、アドオン開発に必要な環境構築を行います。
本書の読者が目的とすることはあくまでモデリングであり、
プログラミングではないという考えのもと、最小限の内容にしています。

== テキストエディタ

アドオンの作成にはPythonというプログラミング言語を使用します。
Pythonスクリプト@<fn>{script}を記述する際、WindowsのNotepad(メモ帳)など
OS標準のテキストエディタでも問題ありませんが、プログラミングがしやすいような
機能が用意されているテキストエディタを使用すると快適に作業ができます。
BlenderのScriptタブにもText Editorエリアが存在するため、簡単なスクリプトを実行したり
小規模なアドオンを作ったりする程度であれば、そちらでも十分です。

別途ソフトウェアをインストールする場合、いくつか選択肢がありますが、
こだわりがなければVisual Studio Code(以降、VSCodeと表記)@<fn>{vscode}から始めると
大抵の作業に対応できます。

//info[Visual StudioとVisual Studio Code]{

Unityを使用している方は、Visual Studioがインストールされているかもしれません。
Visual StudioはIDE（統合開発環境）と呼ばれるツールの一つで、開発に必要な機能がまとまっています。

Visual Studio Codeはコードを書く機能に重点を置いており、Visual Studioと比べて軽量です。

//}

//footnote[script][ スクリプト: スクリプト言語で記述されたソースコード。所謂プログラムのこと。 ]
//footnote[vscode][ https://code.visualstudio.com/ ]
