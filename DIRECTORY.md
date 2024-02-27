Portfolio_PULLCON0.9  
├─ Dxlib(DXライブラリ格納ディレクトリ)  
│      
├─ picojson(C++のJSONパーサpicojson.hが入っているファイル)  
│   
├─ AppFrame  
│　│  
│　└─ source    
│　　　│　appframe.h 作:阿部健太郎(フレームのインクルード済みヘッダー)  
│　　　│  
│　　　├─ Application (エントリーポイントとゲームの入力計算描画が入ったファイル)  
│　　　│　　ApplicationBase.cpp  
│　　　│　　ApplicationBase.h 作:阿部健太郎(アプリケーションの実体となる基底クラス)  
│　　　│　　InputManager.cpp  
│　　　│　　InputManager.h 作:阿部健太郎(入力系をまとめたクラス)  
│　　　│　　WinMain.cpp 作:阿部健太郎(エントリーポイント)  
│　　　│      
│　　　├─ Base(オブジェクトの基底クラスとそれを管理するクラスが入ったファイル)  
│　　　│　　GameBase.cpp  
│　　　│　　GameBase.h 作:阿部健太郎(基底クラス,オブジェクト作る時ここから派生する)  
│　　　│　　GameServerShared.cpp  
│　　　│　　GameServerShared.h 作:阿部健太郎(オブジェクトをシェアードポインタで作りサーバーで管理したいときに使うクラス)  
│　　　│　　GameServerUnique.cpp  
│　　　│　　GameServerUnique.h 作:阿部健太郎(オブジェクトをユニークポインタで作りサーバーで管理したいときに使うクラス)  
│　　　│      
│　　　├─ Math(計算系をまとめたファイル)  
│　　　│　　2dCollision.cpp  
│　　　│　　2dCollision.h 作:阿部健太郎(2次元的当たり判定をまとめたクラス)  
│　　　│　　3dCollision.cpp  
│　　　│　　3dCollision.h 作:阿部健太郎(3次元的当たり判定をまとめたクラス)  
│　　　│　　dx_utility.cpp  
│　　　│　　dx_utility.h 作:阿部健太郎(dxライブラリで使われる構造体と自分の構造体を変換する関数をまとめたファイル)  
│　　　│　　Easing.cpp  
│　　　│　　Easing.h 作:阿部健太郎(イージング関数群をまとめたクラス)  
│　　　│　　math.cpp  
│　　　│　　math.h 作:阿部健太郎(計算系のインクルードファイルをまとめたもの)  
│　　　│　　matrix33.cpp  
│　　　│　　matrix33.h 作:阿部健太郎(3*3行列クラス)  
│　　　│　　matrix44.cpp  
│　　　│　　matrix44.h 作:阿部健太郎(4*4行列クラス)  
│　　　│　　Polar2.cpp  
│　　　│　　Polar2.h 作:阿部健太郎(2次元極座標の計算クラス)  
│　　　│　　Polar3D.cpp  
│　　　│　　Polar3D.h 作:阿部健太郎(3次元極座標の計算クラス)  
│　　　│　　rect.cpp  
│　　　│　　rect.h 作:阿部健太郎(矩形を定義したクラス)  
│　　　│　　utility.cpp  
│　　　│　　utility.h 作:阿部健太郎(その他まとめられない計算関数や円周率など定数を入れた静的クラス)  
│　　　│　　vector2.cpp  
│　　　│　　vector2.h 作:阿部健太郎(2dベクトルの計算クラス)  
│　　　│　　vector4.cpp  
│　　　│　　vector4.h 作:阿部健太郎(3dベクトルの計算クラス)  
│　　　│  
│　　　├─ ResourceServer(画像を管理するクラスが入ったファイル)  
│　　　│　　ResourceServer.cpp  
│　　　│　　ResourceServer.h 作:阿部健太郎 
│　　　│      
│　　　└─ Script(スクリプトのコマンドを処理するクラスとスクリプトの文字を操作すクラスをまとめたファイル)  
│　　　　　CommandBase.h 作:阿部健太郎(コマンド操作するときの基底クラス)  
│　　　　　CommandCrFeedIn.cpp  
│　　　　　CommandCrFeedIn.h 作:阿部健太郎(カラーでフェードインするときに処理するクラス)  
│　　　　　CommandCrFeedOut.cpp    
│　　　　　CommandCrFeedOut.h 作:阿部健太郎(カラーでフェードアウトするときに処理するクラス)  
│　　　　　CommandDrawIn.cpp  
│　　　　　CommandDrawIn.h 作:阿部健太郎(画像をフェードインするときに処理するクラス)  
│　　　　　CommandDrawOut.cpp  
│　　　　　CommandDrawOut.h 作:阿部健太郎(画像をフェードアウトするときに処理するクラス)  
│　　　　　CommandDrawRect.cpp  
│　　　　　CommandDrawRect.h 作:阿部健太郎(四角形を描画するときに処理するクラス)  
│　　　　　CommandDrawString.cpp  
│　　　　　CommandDrawString.h 作:阿部健太郎(文字を描画する時に処理するクラス)  
│　　　　　CommandDrawTime.cpp  
│　　　　　CommandDrawTime.h 作:阿部健太郎(時間を描画する時に処理するクラス)  
│　　　　　CommandImageLoad.cpp  
│　　　　　CommandImageLoad.h 作:阿部健太郎(画像をロードするときに処理するクラス)  
│　　　　　CommandLabel.cpp  
│　　　　　CommandLabel.h 作:阿部健太郎(ラベルを保存するときに処理するクラス)  
│　　　　　CommandMessage.cpp  
│　　　　　CommandMessage.h 作:阿部健太郎(絵を動かしながら音を流すときに処理するクラス)  
│　　　　　CommandMoviePlay.cpp  
│　　　　　CommandMoviePlay.h 作:阿部健太郎(動画を再生させたいときに処理するクラス)  
│　　　　　CommandMusicBack.cpp  
│　　　　　CommandMusicBack.h 作:阿部健太郎(音楽を一回だけ流すコマンドを処理するクラス)  
│　　　　　CommandMusicLoop.cpp  
│　　　　　CommandMusicLoop.h 作:阿部健太郎(音楽をループ再生するときに処理するクラス)  
│　　　　　CommandMusicStop.cpp  
│　　　　　CommandMusicStop.h 作:阿部健太郎(音を止めたいときに処理するクラス)  
│　　　　　CommandSeLoad.cpp  
│　　　　　CommandSeLoad.h 作:阿部健太郎(音をメモリに読み込むときに処理するクラス)  
│　　　　　ScriptsData.cpp  
│　　　　　ScriptsData.h 作:阿部健太郎(jsonファイルの呼び込みクラス)  
│　　　　　ScriptsString.cpp  
│　　　　　ScriptsString.h 作:阿部健太郎(スクリプトに使われる文字列に対するユーティリティ処理)  
│                  
└─ PULLCON0.9  
　　│  
　　└─ PULLCON0.9  
　　　　│  
　　　　└─ source  
　　　　　　│　ApplicationGlobal.cpp  
　　　　　　│　ApplicationGlobal.h 作:阿部健太郎(グローバル変数を置く静的クラス)  
　　　　　　│　ApplicationMain.cpp  
　　　　　　│　ApplicationMain.h 作:阿部健太郎(ゲームの実体となる派生クラス)  
　　　　　　│  
　　　　　　├─ maingame (ゲーム内(ModeMainGame)に登場するオブジェクトをまとめたファイル)  
　　　　　　│　　ActorMainGame.cpp  
　　　　　　│　　ActorMainGame.h 作:中田瑞希(ModeMainGameで使われるオブジェクトの基底クラス)  
　　　　　　│　　AreaCommunication.cpp  
　　　　　　│　　AreaCommunication.h 作:中田瑞希(ボイスを発生させるクラス)  
　　　　　　│　　AreaEnemySpawn.cpp  
　　　　　　│　　AreaEnemySpawn.h 作:中田瑞希(敵を生成するクラス)  
　　　　　　│　　AreaNoEntry.cpp  
　　　　　　│　　AreaNoEntry.h 作:中田瑞希(自由配置できるオブジェクトの当たり判定のクラス)  
　　　　　　│　　AreaSupply.cpp  
　　　　　　│　　AreaSupply.h 作:中田瑞希(燃料回復オブジェクトのクラス)  
　　　　　　│　　Bullet.cpp  
　　　　　　│　　Bullet.h 作:中田瑞希(弾丸クラス)  
　　　　　　│　　EffectBase.cpp  
　　　　　　│　　EffectBase.h 作:中田瑞希(エフェクトの基底クラス)  
　　　　　　│　　EffectDeathObject.cpp  
　　　　　　│　　EffectDeathObject.h 作:中田瑞希(敵を倒したときのエフェクトクラス)  
　　　　　　│　　EffectDestroyAmmo.cpp  
　　　　　　│　　EffectDestroyAmmo.h 作:中田瑞希(弾丸が消滅したときのエフェクトクラス)  
　　　　　　│　　EffectFireGunship.cpp  
　　　　　　│　　EffectFireGunship.h 作:中田瑞希(ガンシップが球を発射したときのエフェクトクラス)  
　　　　　　│　　EffectFirePlayer.cpp  
　　　　　　│　　EffectFirePlayer.h 作:中田瑞希(プレイヤーが球を発射したときのエフェクトクラス)  
　　　　　　│　　EffectHitBlackSmoke.cpp  
　　　　　　│　　EffectHitBlackSmoke.h 作:中田瑞希(プレイヤーのHPが少ない時に出るエフェクトクラス)  
　　　　　　│　　EffectHitPlayerFrame.cpp  
　　　　　　│　　EffectHitPlayerFrame.h 作:中田瑞希(弾丸がヒットした時のエフェクトクラス)  
　　　　　　│　　EffectSpawnAmmo.cpp  
　　　　　　│　　EffectSpawnAmmo.h 作:中田瑞希(弾丸が生まれるときのエフェクト)  
　　　　　　│　　EnemyAAA.cpp  
　　　　　　│　　EnemyAAA.h 作:中田瑞希(敵対空砲クラス)  
　　　　　　│　　EnemyColumn.cpp  
　　　　　　│　　EnemyColumn.h 作:中田瑞希(敵の隊列クラス)  
　　　　　　│　　EnemyGunShip.cpp  
　　　　　　│　　EnemyGunShip.h作:中田瑞希(敵ガンシップクラス)  
　　　　　　│　　EnemyKobae.cpp  
　　　　　　│　　EnemyKobae.h 作:中田瑞希(敵コバエークラス)  
　　　　　　│　　EnemySkyhunter.cpp  
　　　　　　│　　EnemySkyhunter.h 作:中田瑞希(敵スカイハンタークラス)  
　　　　　　│　　GameStage.cpp  
　　　　　　│　　GameStage.h 作:中田瑞希(ゲーム上の土台のクラス)  
　　　　　　│　　Player.cpp  
　　　　　　│　　Player.h 作:中田瑞希(プレイヤークラス)  
　　　　　　│　　SkySphere.cpp  
　　　　　　│　　SkySphere.h 作:中田瑞希(スカイスフェアクラス)  
　　　　　　│　　StageObject.cpp  
　　　　　　│　　StageObject.h 作:中田瑞希(ステージ上のビルなどのオブジェクトクラス)  
　　　　　　│  
　　　　　　├─ mode(画面モードをまとめたファイル)  
　　　　　　│　　ModeMainGame.cpp  
　　　　　　│　　ModeMainGame.h 作:阿部健太郎(ゲームのスクリプトが実装されているクラス)  
　　　　　　│　　ModeSpeakScript.cpp  
　　　　　　│　　ModeSpeakScript.h 作:阿部健太郎(キャラが喋る時に使われるクラス)  
　　　　　　│　　ModeTitle.cpp  
　　　　　　│　　ModeTitle.h 作:阿部健太郎(タイトル画面)  
　　　　　　│      
　　　　　　├─ speakscript(ModeSpeakScript内で使われるオブジェクトをまとめたファイル)  
　　　　　　│　　ActorBaseSpeak.cpp  
　　　　　　│　　ActorBaseSpeak.h 作:阿部健太郎(ModeSpeakScript内で使われるオブジェクトの基底クラス)  
　　　　　　│　　SpeakScriptObject.cpp  
　　　　　　│　　SpeakScriptObject.h 作:阿部健太郎(ゲーム中に動きながら喋るオブジェクト)  
　　　　　　│  
　　　　　　├─ title(タイトル(ModeTitle)内で使われるオブジェクトをまとめたファイル)  
　　　　　　│　　ActorTitle.cpp  
　　　　　　│　　ActorTitle.h 作:阿部健太郎(タイトル画面でのオブジェクトの基底クラス)  
　　　　　　│　　CreditGuid.cpp  
　　　　　　│　　CreditGuid.h 作:阿部健太郎(クレジットの文字を表示するクラス)  
　　　　　　│　　CreditLogo.cpp  
　　　　　　│　　CreditLogo.h 作:阿部健太郎(プレイヤーがクレジットを見る時に引っ張るもののクラス)  
　　　　　　│　　EndGuid.cpp  
　　　　　　│　　EndGuid.h 作:阿部健太郎(エンドの文字を表示するクラス)  
　　　　　　│　　EndLogo.cpp  
　　　　　　│　　EndLogo.h 作:阿部健太郎(プレイヤーがエンドする時に引っ張るもののクラス)  
　　　　　　│　　StartGuid.cpp  
　　　　　　│　　StartGuid.h 作:阿部健太郎(スタート文字を表示するクラス)  
　　　　　　│　　StartLogo.cpp  
　　　　　　│　　StartLogo.h 作:阿部健太郎(ゲームを始めたい時引っ張るもののクラス)  
　　　　　　│　　TitleLogo.cpp  
　　　　　　│　　TitleLogo.h 作:阿部健太郎(タイトルロゴ)  
　　　　　　│　　TitlePlayer.cpp  
　　　　　　│　　TitlePlayer.h 作:阿部健太郎(タイトル画面でのプレイヤー)  
　　　　　　│      
　　　　　　└─ ui(ゲーム上のuiオブジェクトをまとめたファイル)  
　　　　　　　　　UIBase.cpp  
　　　　　　　　　UIBase.h 作:阿部健太郎(ゲーム画面で使われるuiの基底クラス)  
　　　　　　　　　UICursor.cpp  
　　　　　　　　　UICursor.h 作:阿部健太郎(カーソルuiクラス)  
　　　　　　　　　UIFuelGage.cpp  
　　　　　　　　　UIFuelGage.h 作:阿部健太郎(燃料ゲージのクラス)  
　　　　　　　　　UIHpGage.cpp  
　　　　　　　　　UIHpGage.h 作:阿部健太郎(hpゲージのクラス)  
　　　　　　　　　UIPullGage.cpp  
　　　　　　　　　UIPullGage.h 作:阿部健太郎(引張ゲージのクラス)  
　　　　　　　　　UITutorial.cpp  
　　　　　　　　　UITutorial.h 作:阿部健太郎(画面上に表示されるボタンの案内のクラス)  