- okay so the goal is to find the groups
    * a group is a set of all adjacent reaching stones
    * so when you place a stone:
        + if stone->up exists:
            + group becomes stone ... stone->up
        + else if stone->down exists:
            + group becomes stone ... stone->down
        + else if stone->left exists:
            + group becomes stone ... stone->left
        + else if stone->right exists:
            + group becomes stone ... stone->right
    + alright then on next iteration, should we then go into stone=stone->up and then repeat?
