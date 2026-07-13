## 3 確率制御の基礎
### 3.1 最適性の原理
期待総割引便益
$$
J(0, X_0; \{u_t\}) = \mathbb{E}\left[\sum_{t=0}^{T-1}\frac{1}{(1+r)^t}f(X_t,u_t) + \frac{1}{(1+r)^T}g(X_T,u_T)\right] \tag{3.1.1}
$$

価値関数 $V(0, X_0)$：取り得る最大の期待総割引便益  
最適制御 $\{u^\ast_t\}$：最適に実施された制御
$$
V(0,X_0) = \max_{\{u_t\}} J(0, X_0; \{u_t\}) = J(0, X_0; \{u_t^\ast\}) \tag{3.1.2}
$$

#### ベルマンの最適性原理
ある時点 $t$ で最適とされる制御過程は，以降のいかなる時点での最適制御過程も包含していなければならない．  

> 初期状態や最初の決定がいかなるものであっても，残りの決定は，最初の決定によって生じた結果に対して最適制御過程を構成するものでなければならない．

背理法：$\{u_s^\ast\}_{t\leq s\leq T}$ のうち，$\{u_s^\ast\}_{t+1\leq s\leq T}$ の部分が $t+1$ 時点（の状態）で解き直した最適解 $\{u_s^{\ast\ast}\}_{t+1\leq s\leq T}$ と一致しない場合，後者と一致させたほうがより最適な経路となってしまう．

ベルマンの最適性原理から，各時点での価値観数は，その時点より一つ前の時点の価値観数を決定づける

#### 終端時刻が存在する場合

$$
V(T,X_T) = \max_{u_T} g(X_T, u_T) \tag{3.1.3}
$$
としたとき，
$$
\begin{align}
V(T-1,X_{T-1}) &= \max_{u_{T-1}}\left\{f(X_{T-1}, u_{T-1} + \frac{1}{1+r}\mathbb{E}_{T-1}[g(X_T, u_T^\ast)]\right\} \tag{3.1.4} \\
&= \max_{u_{T-1}}\left\{f(X_{T-1}, u_{T-1} + \frac{1}{1+r}\mathbb{E}_{T-1}[V(T, X_T)]\right\} \tag{3.1.5} 
\end{align}
$$
一般に
$$
V(t,X_{t}) = \max_{u_t}\left\{f(X_{t}, u_{t}) + \frac{1}{1+r}\mathbb{E}_{t}[V(t+1, X_{t+1})]\right\} \tag{3.1.6} 
$$
隣り合わない二時点を考えれば，動的計画法方程式
$$
V(s,X_{s}) = \max_{\{u_t\}}\mathbb{E}\left[\sum_{t=s}^{s'-1}\frac{1}{(1+r)^{t-s}}f(X_{t}, u_{t}) + \frac{1}{(1+r)^{s'-s}}[V(s', X_{s'})]\right] \tag{3.1.7} 
$$

#### 終端時刻が存在しない場合
上記で $T$ を限りなく大きくした場合...

仮定：横断性条件
$$
\lim_{t\to\infty} \frac{1}{(1+r)^{T+1}} \mathbb{E}[g(X_T, u_T)] = 0 \tag{3.1.8}
$$
の下，期待割引総便益 $J$
$$
J(X_0; \{u_t\}) = \mathbb{E}\left[\sum_{t=0}^{\infty}\frac{1}{(1+r)^t}f(X_t,u_t) \right] \tag{3.1.9}
$$
となって，時間 $t$ に依存しない．動的計画法方程式は
$$
V(x) = \max_{u}\left\{f(x, u) + \frac{1}{1+r}\mathbb{E}_{t}[V(x')]\right\} \quad \text{ただし }x'=X_1\tag{3.1.10} 
$$

### 3.2 HJB 方程式
最適性の原理を連続時間モデルに当てはめよう

#### 3.2.1 HJB 方程式の導出 -- 有限時間設定
状態変数 $X_t$ は以下の確率微分方程式に従う
$$
\mathrm{d}X_t = \mu(t,X_t,u_t)\,\mathrm{d}t + \sigma(t,X_t,u_t)\,\mathrm{d}W_t
\tag{3.2.1}
$$

期待総割引便益
$$
J(t, x_t; \{u_s\}) = \mathbb{E}_{t,x_t}\left[\int_{t}^{T}\mathrm{e}^{-r(s-t)}f(s,X_s,u_s)\,\mathrm{d}s + \mathrm{e}^{-r(T-t)}g(X_T)\right] \tag{3.2.2}
$$

仮定①：リプシッツ条件  
仮定②：二次の成長条件  
仮定③：可積分条件  
=> 非現実的な状態変数の振る舞い・$J$ が無限大に発散してしまうような状況を排除

価値関数 $V(t,x_t)$ と最適制御 $\{u_s^\ast\}$
$$
V(t,x_t) = \max_{\{u_s\}} J(t, x_t; \{u_s\}) - J(t,x_t;\{u_s^\ast\})
$$

（有限時間）絶対連続制御問題
$$
\max_{\{u_s\}} J(t, x_t; \{u_s\}),\quad \text{subject to}\ (3.2.1)
$$

ベルマンの最適性原理を適用する．  
まず，$[t, t+\mathrm{d}t]$ と $[t+\mathrm{d}t, T]$ に分割して考える
$$
\begin{align}
V(t,x_t) &= \max_{\{u_s\}_{t\leq{}s\leq{}t+\mathrm{d}t}}\mathbb{E}_{t,x_t}\left[\int_{t}^{t+\mathrm{d}t}\mathrm{e}^{-r(s-t)}f(s,X_s,u_s)\,\mathrm{d}s\right. \notag\\
&+ \left.\max_{\{u_s\}_{t+\mathrm{d}t\leq{}s\leq{}T}}\mathbb{E}_{t+\mathrm{d}t, x_t+\mathrm{d}X_t}\left[\int_{t+\mathrm{d}t}^T\mathrm{e}^{-r(s-t)}f(s,X_s,u_s)\,\mathrm{d}s + \mathrm{e}^{-r(T-t)}g(X_T)\right]\right]\tag{3.2.6}
\end{align}
$$
右辺第二項は...
$$
\begin{align}
\text{（右辺第二項）} &= \mathrm{e}^{-r\,\mathrm{d}t} \max_{\{u_s\}_{t+\mathrm{d}t\leq{}s\leq{}T}}\mathbb{E}_{t+\mathrm{d}t, x_t+\mathrm{d}X_t}\left[\int_{t+\mathrm{d}t}^T\mathrm{e}^{-r(s-(t+\mathrm{d}t))}f(s,X_s,u_s)\,\mathrm{d}s + \mathrm{e}^{-r(T-(t+\mathrm{d}t))}g(X_T)\right] \notag\\
&= \mathrm{e}^{-r\,\mathrm{d}t} V(t+\mathrm{d}t, x_t + \mathrm{d}X_t) \tag{3.2.7}
\end{align}
$$
より結局
$$
\begin{align}
V(t,x_t) &= \max_{\{u_s\}_{t\leq{}s\leq{}t+\mathrm{d}t}}\mathbb{E}_{t,x_t}\left[\int_{t}^{t+\mathrm{d}t}\mathrm{e}^{-r(s-t)}f(s,X_s,u_s)\,\mathrm{d}s + \mathrm{e}^{-r\,\mathrm{d}t} V(t+\mathrm{d}t, x_t + \mathrm{d}X_t)\right] \tag{3.2.8} \\
&\simeq \max_{\{u_s\}_{t\leq{}s\leq{}t+\mathrm{d}t}}\mathbb{E}_{t,x_t}\left[\int_{t}^{t+\mathrm{d}t}\mathrm{e}^{-r(s-t)}f(s,X_s,u_s)\,\mathrm{d}s + (1-r\,\mathrm{d}t) V(t+\mathrm{d}t, x_t + \mathrm{d}X_t)\right] \tag{3.2.9}
\end{align}
$$
伊藤の公式より
$$
\begin{align}
V(t+\mathrm{d}t, x_t + \mathrm{d}X_t) &= V(t,x_t) + \left[V_t(t,x_t) + \mu V_X(t,x_t) + \frac{1}{2}\sigma^2V_{XX}(t,x_t)\right]\mathrm{d} t + \sigma V_X(t,x_t)\mathrm{d}W_t \tag{3.2.11}\\
\mathbb{E}_{t,x_t}[V(t+\mathrm{d}t, x_t + \mathrm{d}X_t)] &= V(t,x_t) + \left[V_t(t,x_t) + \mu V_X(t,x_t) + \frac{1}{2}\sigma^2V_{XX}(t,x_t)\right]\mathrm{d} t \tag{3.2.12}
\end{align}
$$
なので
$$
(1-r\,\mathrm{d}t) V(t+\mathrm{d}t, x_t + \mathrm{d}X_t) = V(t,x_t) + \left[V_t(t,x_t) + \mu V_X(t,x_t) + \frac{1}{2}\sigma^2V_{XX}(t,x_t) - rV(t,x_t)\right]\mathrm{d} t \tag{3.2.13}
$$

以上および $\mathrm{d}t\to0$ の極限から **HJB 方程式**（有限時間）
$$
\begin{align}
&\max_{u_t}\left[f(t,x_t,u_t) + V_t(t,x_t) + \mu V_X(t,x_t) + \frac{1}{2}\sigma^2V_{XX}(t,x_t) - rV(t,x_t)\right] = 0 \tag{3.2.14}\\
&\text{終端条件}\qquad V(T,X_T) = g(X_T) \tag{3.2.15}
\end{align}
$$
偏微分作用素 $\mathcal{L}$ を定義すれば
$$
\begin{align}
&\max_{u_t}\left[\mathcal{L}V(t,x_t) + f(t, x_t, u_t\right] = 0 \tag{3.2.17}\\
&\text{終端条件}\qquad V(T,X_T) = g(X_T) \tag{3.2.15}\\
& \mathcal{L} \equiv \frac{1}{2}\sigma^2 \frac{\partial^2}{\partial X^2} + \mu\frac{\partial}{\partial X} + \frac{\partial}{\partial t} - r \tag{3.2.16}
\end{align}
$$

#### 3.2.2 HJB 方程式の導出 -- 無限時間設定
期待総割引便益と価値関数
$$
\begin{align}
J(x_t; \{u_s\}) &= E_{x_t}\left[\int_t^\infty \mathrm{e}^{-r(s-t)}f(X_s,u_s)\,\mathrm{d}s\right] \tag{3.2.19} \\
V(x_t) &= \max_{\{u_s\}} J(x_t; \{u_s\}) = J(x_t; \{u^\ast_s\}) \tag{3.2.20}
\end{align}
$$
を出発点に，3.2.1 節とほぼ同じ議論
- $[t, t+\mathrm{d}t]$ と $[t+\mathrm{d}t, \infty]$ に分割
- 後半部分を次のステップの価値関数 $V(x_t+\mathrm{d}X_t)$ で表す
- 極限とる

**HJB 方程式**（無限時間）
$$
\max_{u_t}\left[f(x_t,u_t) + \mu V'(x_t) + \frac{1}{2}\sigma^2V''(x_t) - rV(x_t)\right] = 0 \tag{3.2.24}\\
$$
もしくは
$$
\begin{align}
&\max_{u_t}\left[\mathcal{L}V(x_t) + f(x_t, u_t\right] = 0 \tag{3.2.26}\\
&\mathcal{L} \equiv \frac{1}{2}\sigma^2 \frac{\mathrm{d}^2}{\mathrm{d} x^2} + \mu\frac{\mathrm{d}}{\mathrm{d} x} - r \tag{3.2.25}
\end{align}
$$

