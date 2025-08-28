 <h1>📊 Backtesting Engine</h1>
 <h3>A High-Performance C++ Engine with Python Strategy Interface</h3>

 <p>
  <img src="https://img.shields.io/badge/C++-20-blue" alt="C++ 20">
  <img src="https://img.shields.io/badge/Python-3.10+-green" alt="Python 3.10+">
  <img src="https://img.shields.io/github/license/johndcode/Backtesting-Engine" alt="License">
</p>

 ---

 ### ✨ Overview
 This Backtesting Engine Framework is a quantitative trading simulation framework written in C++ for performance
 with a Python interface for strategy scripting. It allows traders, researchers, and developers
 to rigorously test trading strategies before deploying to live markets.

 #### 🚀 Current features include:
 - Fast, event-driven C++ simulation core
 - Market data ingestion from CSV or API
 - Order management with queue priority & latency simulation
 - Realistic trading mechanics (slippage, latency, corporate actions, short selling, stock splits, dividend payments)
 - Portfolio & PnL tracking
 - Python bindings (via pybind11) for strategy scripting
 - High-level Python API (buy(), sell(), etc.) without exposing raw orders

 ---

 ### ⚙️Release

The framework is distributed as a Python extension module (.so) that users can build on to create their own backtesters.

(The module is published [here](https://github.com/JohnDCode/Backtesting-Engine-Publish))

---

 ### 📄Documentation
 
For the full development story and detailed writeup, check out the blog post here:  
[My Backtesting Engine Framework](https://www.johndcode.com/posts/Backtesting-Engine/)  

 ---

 ### 🔮 Roadmap
 Planned features for future versions:
 - Support for short-selling with margin constraints
 - Slippage & market impact simulation
 - Survivorship bias elimination (data cleaning tools)
 - Walk-forward testing & cross-validation modules
 - Expanded metrics: Sharpe, Sortino, drawdowns, exposure

 ---

### 📫 Contact Me  
- 📧 Email: **johndavidabe101@gmail.com**  
- 💼 LinkedIn: [linkedin.com/in/johndcode](https://linkedin.com/in/johndcode)  
- 🧑‍💻 GitHub: [github.com/johndcode](https://github.com/johndcode)  

 ⭐ If you like this project, consider giving it a star on GitHub!
