## 4 より高度な確率制御
### 前回の復習
特異制御問題
$$
\begin{align}
\max_{\{\eta_t\}}\ &\mathbb{E}\left[\int_o^\infty \mathrm{e}^{-rt}f(X_t)\,\mathrm{d}t - k\int_0^\infty \mathrm{e}^{-rt}\,\mathrm{d}\eta_t\right] \tag{4.2.30} \\
\text{subject to}\quad&\mathrm{d}X_s = \mu(X_t)\,\mathrm{d}t + \sigma(X_t)\,\mathrm{d}W_t + \mathrm{d}\eta_t \tag{4.2.31} \\
&\text{ただし，$\eta_t$は右連続非減少過程：} \eta_t\equiv\int_0^t u_s\,\mathrm{d}s \tag{4.2.32}
\end{align}
$$
(4.2.30) の後半は入力に対するコストであり，$\eta_t$の増分に比例する値を現在値換算して総和を取ったもの．
$$
k\int_0^\infty \mathrm{e}^{-rt}\,\mathrm{d}\eta_t. \tag{4.2.33}
$$
この問題の最適制御は，
$$
\begin{cases}
\text{制御しない}&X_t\in\mathcal{H}\equiv\{x;x>\alpha\} \\
\text{制御実施}&X_t\not\in\mathcal{H}
\end{cases}
$$
$\partial\mathcal{H}$でのみ制御がなされて，その境界から離れた瞬間に元の制御のない状態に戻る．  
$\implies$結果的に$\eta_t$は実際上殆どの時間で連続的に増加する．

### 4.3 インパルス制御
特異制御においては，境界から続行領域の内側深くまで状態変数を押し戻すような制御してまで (4.2.33) の部分を大きくする必要がない．  
$\implies$状態変数にジャンプが起きるようなことは事実上ない．

#### 4.3.1 固定費とインパルス
(4.2.33) を書き換える．  
制御が起こる時点：$\{\tau_0,\tau_1,\dots\}$  
各時点$\tau_i\sim\tau_i+\Delta\tau_i$の$\eta_t$の変化幅：$\Delta\eta_t$
$$
k\int_0^\infty \mathrm{e}^{-rt}\,\mathrm{d}\eta_t = \sum_{i=0}^\infty k\int_{\tau_i}^{\tau_i+\Delta\tau_i}\mathrm{e}^{-rt}\,\mathrm{d}\eta_t\simeq\sum_{i=0}^\infty \mathrm{e}^{-r\tau_i}k\Delta\eta_{\tau_i} \tag{4.3.1}
$$
この項は制御実施のたびに発生するコストの現在価値の総和．  
$\implies$制御の回数は少ないほうが良く，制御の幅（規模）も小さいほど良い．  
特異制御においては制御幅の最小化ゆえに状態変数のジャンプがない．

これを元に問題 (4.2.30)(4.2.31) を改変する．  
$k\Delta\eta_i$をより一般的に$\eta_t$の増分の関数として考える．
$$
\begin{align}
\text{（増加関数）}&K:\mathbb{R}_+\cup\{0\}\to\mathbb{R}\notag\\
&K(\Delta\eta_t) \tag{4.3.2}\\
&K(0_+)>0,\quad K(0) = 0 \tag{4.3.3}\\
\text{（劣加法性）}&K(\zeta+\zeta') \leq K(\zeta) + K(\zeta')  \tag{4.3.4} \\
\text{（例えば）}&K(\zeta) =
\begin{cases}
k_f + k_p\zeta,&\zeta>0 \\
0,&\zeta\leq0
\end{cases}
\tag{4.3.5}
\end{align}
$$
$k_f$は固定費用，$k_p\zeta$は比例費用．

コスト部分の違い：
- $k\Delta\eta_t$  
  制御がなされるのは状態変数が領域からはみ出ないようにするため．  
  状態変数が境界上にとどまり続けることもあり得る．
- $K(\Delta\eta_t)$  
  小刻みな制御は最適ではありえず，制御は極力実施しないほうが良い．  
  制御を実施する時点を厳選し，制御実施の継続時間も極力短くすべし．

「原点において不連続で，列下方的な費用関数のもとでは，制御は$\eta_t$の瞬間的なジャンプのみとなり，その時点の選択と，その場合の$\Delta\eta_t$の幅（規模）が，求めるべき最適解と構成する．」

インパルス制御問題：
$$
\begin{align}
&\sup_v\mathbb{E}\left[\int_0^\infty\mathrm{e}^{-rt}f(X_t)\,\mathrm{d}t-\sum_{i=0}^\infty\mathrm{e}^{-r\tau_i}K(\zeta_i)\mathbb{1}_{\{\tau_i\}}\right]\tag{4.3.9}\\
\text{subject to}&\notag\\
&\begin{cases}
\mathrm{d}X_t = \mu(X_t)\,\mathrm{d}t+\sigma(X_t)\,\mathrm{d}W_t,&\tau_i\leq t\leq\tau_{i+1}<\infty \\
X_{\tau_i}=X_{\tau_i-}+\zeta_i,&\\
X_{0-}=x
\end{cases}\tag{4.3.6}\\
&v=\{(\tau_i,\zeta_i)\}_{i\geq0}\tag{4.3.10}
\end{align}
$$

#### 4.3.2 準変分不等式
価値関数$V$は，初期値$x$のみの関数（初期値以降の状態変数変動は制御の仕方によって決まる）．

インパルス制御の特徴：制御実施の判定とその幅（規模）も同時に決める

時間感覚$[t,t+\mathrm{d}t]$を考える
- 今すぐ制御を実施する場合（$t=\tau$）
  $$
  \begin{align}
  V(X_{t-})
  &=\sup_\zeta\left[-K(\zeta)+\mathbb{E}_{X_{t-}}\left[\int_t^{t+\mathbb{d}t}\mathrm{e}^{-rs}f(X_{s-}+\zeta)\,\mathrm{d}s+\mathrm{e}^{-r(t+\mathrm{d}t)}V(X_{t-}+\zeta+\mathrm{d}X_t)\right]\right] \tag{4.3.12} \\
  &=\sup_\zeta\left[-K(\zeta)+\mathbb{E}_{X_{t-}}\left[\int_t^{t+\mathbb{d}t}\mathrm{e}^{-rs}f(X_{s})\,\mathrm{d}s+\mathrm{e}^{-r(t+\mathrm{d}t)}V(X_{t}+\mathrm{d}X_t)\right]\right] \tag{4.3.14}
  \end{align}
  $$
- 今すぐ制御を実施しない場合（$t\neq\tau$）
  $$
  V(X_{t-})=\mathbb{E}_{X_{t-}}\left[\int_t^{t+\mathbb{d}t}\mathrm{e}^{-rs}f(X_{s-})\,\mathrm{d}s+\mathrm{e}^{-r(t+\mathrm{d}t)}V(X_{t-}+\mathrm{d}X_t)\right] \tag{4.3.13}
  $$

制御が実施され (4.3.14) の直後には (4.3.13) が適用される（$t_{-}$に$t$を適用させる）
$$
\begin{align}
V(X_{t-})&=\sup_{\zeta}[-K(\zeta)+\mathbb{E}_{X_{t-}}[\mathbb{E}_{X_t}[V(X_t)]]] \notag \\
&=\sup_{\zeta}[-K(\zeta)+\mathbb{E}_{X_{t-}}[V(X_t)]] \notag \\
&=\sup_{\zeta}[-K(\zeta)+\mathbb{E}_{X_{t-}}[V(X_{t-}+\zeta)]] \notag \\
&=\sup_{\zeta}[-K(\zeta)+V(X_{t-}+\zeta)] \tag{4.3.18}
\end{align}
$$

以下では初期時点$t=0,X_0=x$を考える．  
- この時点で制御をすぐに実施する場合，
  $$
  \begin{align}
  V(x)&=\sup_\zeta[-K(\zeta)+V(x+\zeta)] \tag{4.3.19}\\
  &\equiv\mathcal{M}V(x)\tag{4.3.21}
  \end{align}
  $$
- 今すぐ制御しない場合，通常の HJB 方程式の導出と同様，テイラー展開して，$\mathrm{d}t\to0$ とすると
  $$
  \begin{align}
  0&=f(x)-rV(x)+\mu(x)V'(x)+\frac{1}{2}\sigma(x)^2V''(x)\tag{4.3.22} \\
  &=f(x)+\mathcal{L}V(x)\tag{4.3.23}
  \end{align}
  $$

(4.3.21) (4.3.23) のいずれか一方が成り立つ．  
他方は価値観数より小さくなっていることから不等号$>$が成立する．  
準変分不等式
$$
\begin{gather}
V(x)\geq\mathcal{M}V(x) \tag{4.3.24} \\
0\geq f(x)+\mathcal{L}V(x) \tag{4.3.25} \\
[\mathcal{L}V(x)+f(x)][V(x)-\mathcal{M}V(x)] = 0 \tag{4.3.26}
\end{gather}
$$

### （5.4 応用例）
#### 5.4.1 企業の配当政策
- 状態変数 $X_t$：企業のキャッシュリザーブ
- コスト $k_f + k_p\Delta\eta_t$：固定費用（配当支払いの意思決定に関わる費用）と配当額に比例した費用（税金等）
- 制御：配当支払いの回数とその規模

#### 5.4.2 固定費用を伴う再生可能資源採取
- 状態変数 $X_t$：再生可能資源のストック
- 便益 $p\Delta\eta_t - k_0$：資源価格 $p$ により得られる収入と固定費
- 制御：再生可能資源の採取量
 

### 4.4 確率制御問題の類型
| 問題の特徴 | 定式化 | 制御形式 | 最適性の条件式 |
| :--: | :--: | :--: | :--: |
| 全変数が連続関数 | 絶対連続制御問題 | 状態変数に対する連続的な制御 | HJB 方程式 |
| 停止判断によって状態変数が固定 | 最適停止問題 | 続行領域の設定と境界での停止判定 | 変分不等式 |
| 制御量に比例的な費用・便益 | 特異制御問題 | 続行領域の設定と境域内に留める操作 | 変分不等式 |
| 制御に要する費用が不連続・劣加法 | インパルス制御問題 | 続行領域の設定と境域内部に押し返す操作 | 準変分不等式 |




