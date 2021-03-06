# %%
import random
import sys

import matplotlib.animation as anim
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from mpl_toolkits.mplot3d import Axes3D

ANIMATE = True

# %%
class PlotTraj:
    def __init__(
        self,
        namesBodies,
        massBodies,
        radBodies,
        df: pd.DataFrame,
        noBodies=None,
        noSimSteps=None,
        colors=None,
    ) -> None:

        self.namesBodies = namesBodies
        self.massBodies = massBodies
        self.radBodies = radBodies
        self.df = df

        if noBodies is None:
            self.noBodies = int(df.shape[1] / 3)
        else:
            self.noBodies = noBodies

        if noSimSteps is None:
            self.noSimSteps = int(df.shape[0])
        else:
            self.noSimSteps = noSimSteps

        if colors is None:
            temp = ["b", "g", "r", "c", "m", "y"]
            if self.noBodies <= len(temp):
                self.colors = temp[: self.noBodies]
            else:
                self.colors = temp + ["k"] * (self.noBodies - len(temp))

        else:
            self.colors = colors

    def get_min_max(self):
        maxRad = []
        x = self._update(0)
        for no in range(self.noBodies):
            temp = np.linalg.norm(x[3 * no : (3 * no + 2)])
            maxRad.append(temp)
        return max(maxRad)

    def _update(self, stepIdx):
        datRow = self.df.iloc[stepIdx, :].values
        return datRow

    def static_plot(self, setmax=True, NRows=None, sunPosi=True):
        if NRows == None:
            NRows = self.df.shape[0]
        fig = plt.figure(figsize=(10, 10))
        ax = fig.add_subplot(111, projection="3d")
        if sunPosi is True:
            ax.scatter(0, 0, c="k", s=100)
        if setmax == True:
            maxRad = self.get_min_max()
            offset = maxRad * 0.05
            ax.set_xlim(-maxRad - offset, maxRad + offset)
            ax.set_ylim(-maxRad - offset, maxRad + offset)
            ax.set_zlim(-maxRad - offset, maxRad + offset)
        for no in range(self.noBodies):
            xArr = self.df.iloc[:NRows, 3 * no].values
            yArr = self.df.iloc[:NRows, 3 * no + 1].values
            zArr = self.df.iloc[:NRows, 3 * no + 2].values
            ax.plot(xArr, yArr, zArr, c=self.colors[no % 10])
            ax.scatter(xArr[-1], yArr[-1], zArr[-1], c=self.colors[no % 10])

    def animate(
        self,
        history=True,
        tempo=50,
        stepRow=10,
        setmax=True,
        NRows=None,
        centerDot=True,
        filename="orbit_out.gif",
    ):
        if NRows == None:
            NRows = self.df.shape[0]
        dfAnim = self.df.iloc[
            :NRows:stepRow,
        ]

        fig = plt.figure()
        fig.set_figheight(15)
        fig.set_figwidth(15)
        ax = fig.add_subplot(111, projection="3d")

        def configure_ax(ax):
            maxRad = self.get_min_max()
            offset = maxRad * 0.05
            ax.set_xlim(-maxRad - offset, maxRad + offset)
            ax.set_ylim(-maxRad - offset, maxRad + offset)
            ax.set_zlim(-maxRad - offset, maxRad + offset)

        def animate_step(stepIdx):
            ax.clear()
            if setmax == True:
                configure_ax(ax)
            for no in range(self.noBodies):
                hist_idx = stepIdx * stepRow
                xArr = dfAnim.iloc[stepIdx, :].values
                if history is True:
                    xHist = self.df.iloc[:hist_idx, 3 * no].values
                    yHist = self.df.iloc[:hist_idx, 3 * no + 1].values
                    zHist = self.df.iloc[:hist_idx, 3 * no + 2].values
                    ax.plot(xHist, yHist, zHist, c=self.colors[no % 10])
                ax.scatter(
                    xArr[3 * no],
                    xArr[3 * no + 1],
                    xArr[3 * no + 2],
                    c=self.colors[no % 10],
                )  # self.colors[no%10]
                if centerDot is True:
                    ax.scatter(0, 0, c="k", s=100)

        max_frames = int(np.floor(self.noSimSteps / stepRow))
        ani = anim.FuncAnimation(
            fig,
            animate_step,
            frames=np.arange(0, max_frames),
            interval=tempo,
            repeat=False,
            save_count=sys.maxsize,
        )
        ani.save(filename)


# %%
data = pd.read_csv("data.csv", sep=",", header=None)


# %%
## Extract Moon relative to earth
dataEarth = data.iloc[:, 3:6]
dataMoon = data.iloc[:, 6:9]
dataMoonRel = pd.DataFrame(dataMoon.values - dataEarth.values)

# %%
AnimSys = PlotTraj(
    ["Earth", "Moon"], [1, 1], [1, 1], dataMoonRel
)  # data.iloc[:, 3:9] (only last 2 bodies)
AnimSys.static_plot(setmax=False, NRows=None, sunPosi=False)


# %%
if ANIMATE is True:
    AnimSys.animate(
        stepRow=1,
        setmax=False,
        history=False,
        centerDot=False,
        NRows=1000,
        filename="Test.gif",
    )

# %%
