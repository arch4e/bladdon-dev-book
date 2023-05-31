= より高度なアドオンを開発したい方へ

本書の想定読者はプログラミングの知識がない層ですが、
もう少し詳しくアドオン開発について学びたい方向けにTipsを紹介します。
本編の内容よりも知識が必要になるため付録という形をとっています。
書いてあること全てを実践する必要はなく、自分がやりたいことは何か、
そのために必要なことは何かという視点で必要な情報だけ拾っていただければ十分です。

== 公式ドキュメント等のチュートリアルを実践する

最初からある程度の知識があれば都度ドキュメントを参照する程度で進められますが、
プログラミングに関する知識があまりなく、それでも高度なアドオン開発がしたい方は
公式ドキュメントのチュートリアルを実践することをお勧めします。
特に、Pythonのチュートリアルは日本語にも対応しておりPython自体は汎用性のあるプログラミング言語であるため
学んでおけば（Blenderに限らず）いずれ役に立つこともあるかと思います。

  * @<code>{Python}: https://docs.python.org/ja/3/tutorial/index.html
  * @<code>{Blender Python API}: https://docs.blender.org/api/current/info_quickstart.html

== 既存のUIからコードを確認する

UIを作る際、既存の要素を見て"これはどう実装するんだ？"と気になることがあります。
そんなときに、Blenderから対象のソースコードに飛ぶ方法があるため紹介します。

例として、Toolタブの"Active Tool"パネルがどのように実装されているか確認してみます。

//image[active_tool_panel][Active Toolパネル]{
//}

まず、PreferenceのInterfaceにある"Developer Extras"オプションを有効にします。
その後、コードを見たいUIを右クリックすると"Edit Source"と表示される@<fn>{edit_source}ため、
これをクリックします。

//image[developer_extras_option][Developer Extrasオプション]{
//}

続けてScriptingタブに移動し、Text Editorエリア上部の本のようなボタンを押すと、
Pythonファイルのリストが表示されます。
その中の1つとしてさきほど"Edit Source"を押した要素が定義されているファイルが選択できるようになっており、
ファイルを読み込むことで対応するコードを確認することができます。

//image[edit_source][Edit Source]{
//}

//image[code][Active ToolパネルのUIを定義しているコード]{
//}

//warning[コードの扱いについて]{
既存UIのコードを書き換えて保存すると、実際に変更がBlenderに反映されます。
もしコードを変更・削除した場合UIが表示されなくなったりバグの原因になったりするため
扱う際には十分に注意してください。
//}

//footnote[edit_source][ 要素によっては"Edit Source"が表示されないものもあります。 ]

== Git

本節ではGitとGitHubについて取り上げます。
Gitはバージョン管理ツールの名称であり、GitHubはWebサービスの名称です。
GitHubの類似サービスとしては、GitLab@<fn>{gitlab}やBitbucket@<fn>{bitbucket}が有名です。

GitHubというWebサイトはアドオンの配布などで見かける方も多いと思います。
Gitというバージョン管理ツールを使用しているプロジェクトを
GitHub上に登録し、コードを公開することで他のユーザがライセンスの範囲内でコードを使用したり、
Pull Request（加筆・修正の依頼）を送ったりしやすくなります。

簡単に、GitのインストールからGitHubへのpushまでの流れを紹介します。

=== Gitのインストール

まずは、gitのインストールを行います。
macOSを使用している場合は、Terminal.appで
次のいずれかのコマンドを実行してインストールすると手軽です。
なお、"Homebrewを使用する"ではHomebrew@<fn>{homebrew}をインストールしている必要があります。

//list[][xcode-selectを使用する][shell]{
xcode-select --install
//}

//list[][Homebrewを使用する][shell]{
brew install git
//}

Windowsを使用している場合は、次のいずれかの方法がシンプルです。
下記の方法はGitのWebサイト@<fn>{git}の内容と同じです。
バージョンアップで変更されている可能性もあるため、実行前にGitのWebサイトを確認してください。

  * Standalone Installerをダウンロードし、実行する
  * Portable Installerをダウンロードし、展開する
  ** pathの通し方がわからない場合は非推奨
  * winget@<fn>{winget}を使用する
  ** 最も手軽
  ** 環境によっては手動で有効化する必要がある

今回はwingetを使用することにします。
PowerShellかCommand Promptを起動してください。
これらのツールはWindowsキーを押して出てくるウィンドウか、
Windowsキー + Rで出てくるウィンドウで"powershell"または"cmd"と入力することで呼び出すことができます。

//image[powershell][PowerShell]{
//}

いずれかのソフトウェアを起動したら、次のコマンドを入力します。
@<code>{#}で始まる行はコメントのため無視してください。

//list[][][]{
# wingetのバージョンを確認
# エラーが表示されたら、wingetが使用できる状態でない
winget -v

# gitのバージョンを確認
# インストール前のためエラーが表示されるはず
git -v
//}

//image[version_check][コマンド実行結果]{
//}

wingetがインストールされており、gitがインストールされていないことが確認できたら、
GitのWebサイトに記載されているコマンドを実行します。
実行後、ポップアップウィンドウが出るため、内容を確認して続行します。

//list[][][]{
winget install --id Git.Git -e --source winget
//}

少し待つと、インストールが完了します。
バージョン確認のコマンドを実行すると、インストールされたGitのバージョンが表示されるはずです。

//image[install_git][Gitのインストール]{
//}

続いて、GUIクライアントをインストールします。
コマンドによるGit操作ができる方はGUIクライアントのインストールはしなくても問題ありません。
GUIクライアントもGit公式のものからサードパーティのものまで、様々なソフトウェアがリリースされています。
今回はGitHub Desktopを使用することにします。

//image[github_desktop_website][GitHub Desktopの配布ページ]{
//}

GitHub DesktopのWebサイト@<fn>{github_desktop}にアクセスし、インストーラーをダウンロード・実行してください。
インストールが完了すると、次のような画面が表示されると思います。

//image[github_desktop][GitHub Desktop]{
//}

GitHubにコードをpush（アップロード）する予定があれば、サインインしておきましょう。
"Sign in to GitHub.com"を選ぶとWebブラウザでログイン画面が開きます。
認証後、権限の承認をしたら設定画面に遷移します。
ここで入力する情報は公開されるため、メールアドレスを隠しておきたい場合は自動入力のアドレスのままにしておきましょう。

//image[authorize][権限の承認]{
//}

//image[configure][Gitの設定画面]{
//}

以上で設定は完了です。


//footnote[gitlab][ https://gitlab.com/ ]
//footnote[bitbucket][ https://bitbucket.org/ ]
//footnote[homebrew][ https://brew.sh/ ]
//footnote[git][ https://git-scm.com/download/win ]
//footnote[winget][ https://learn.microsoft.com/ja-JP/windows/package-manager/winget/ ]
//footnote[github_desktop][ https://desktop.github.com/ ]

=== repositoryの作成

メニューに表示されている項目から、目的に合うものを選択します。
なお、"Repository"とはUnityにおけるプロジェクトのような認識で問題ありません。

//image[github_desktop_top][GitHub Desktopのトップ画面]{
//}

  * @<code>{Create a tutorial ...}: （省略）
  * @<code>{Clone a repo...}: インターネット上のrepositoryをクローン（複製）する
  * @<code>{Create a New Repo...}: 新しいrepositoryを作成する
  * @<code>{Add an Exist...}: ローカルのrepositoryをGitHub Desktopで管理する

今回は新しくrepositoryを作成するため、"Create a New Repo..."を選択します。
続けて、設定項目の入力をしていきます。
本書で作成したアドオンのrepositoryを作る場合は次のようになります。

//image[create_new_repo][repositoryの設定]{
//}

  * @<code>{Name}: repository名
  * @<code>{Description}: repositoryの概要
  * @<code>{Local path}: repositoryの保存場所
  * @<code>{Git ignore}: Git管理の対象から外す項目の指定。自動生成ファイルなどを追跡しないようにする。
  * @<code>{License}: repositoryのデータに設定するライセンスを指定する。

"Create repository"を押すと、指定したpathにrepositoryが作成されます。
作成されたディレクトリ（フォルダ）には複数のデータが格納されていますが、
これらはそのままで問題ありません。

//image[repository][作成されたrepository]{
//}

=== Gitによるバージョン管理

本書で作成したアドオンをGitで管理してみます。
@<chap>{create_uiless_addon}で作成したUIなしのスクリプトを
repositoryに追加します。

GitHub Desktopを見ると、追加したファイルの内容が表示されていることがわかります。
追加したファイルにチェックが入っていることを確認したら、"Commit to ~"を押してcommitします。
commitとはゲームにおけるセーブのようなものです。灰色の文字が書かれている場所は
commit messageを記入する場所ですが、慣れるまでは自動入力（空白）のままでよいでしょう。

//image[stage_1][]{
//}

commitすると、ファイルを追加する前の画面に戻ります。
続けて、スクリプトの内容を@<chap>{create_ui}で作成したものに更新します。
ファイルを上書き保存してGitHub Desktopに戻ると、ファイルの更新内容が反映されています。
表示を見ると、行ごとに変更なし・追加・削除が分けられていることがわかります。
このように、Gitはテキストファイルの差分を記録することができます。

//image[stage_2][]{
//}

先ほどと同様にcommitしたら、"History"タブを確認してみてください。
この画面では、これまでのcommit log（変更履歴）が確認できます。

//image[history][]{
//}

Gitを使用すると、上記のように差分管理をしたりファイルを以前の内容に書き戻したりできます。
また、branchという機能を利用して異なる変更をそれぞれ分けて管理したり、
分けて更新していた内容を統合（merge）したりできます。
Gitを使う中で、興味が出てきたら各自で調べてみてください。

=== remote repositoryへのpush

作業をしているPCに保存しているrepositoryをlocal repository、
外部のrepositoryをremote repositoryといいます。
また、local repositoryの内容をremote repositoryに反映させる操作をpushといいます。
そして、remote repositoryの内容をlocal repositoryに反映させる操作をpullといいます。
実際のところ、pullは裏でfetchとmergeを行っているのですが、本題から逸れるため説明は省略します。

GitHubにrepositoryをpushするには、ウィンドウ上部の"Publish repository"をクリックします。
初回はGitHub上での設定を入力するウィンドウが出てきます。
コードを公開したくない場合は"Keep this code private"にチェックを入れ、
公開したい場合はチェックを外して"Publish repository"をクリックします。

//image[push][local repositoryをpushするボタン]{
//}

//image[publish][各項目を確認・更新しPublishする]{
//}

少し待つとGitHubにrepositoryがpushされます。
以上でGit関連の説明は終了です。

//image[remote_repo][GitHubにpushされたrepository]{
//}
