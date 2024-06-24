
Contributing Guidelines
=======================

The main workflow we have to accept contributions is via [forks and pull-requests](https://guides.github.com/activities/forking).

**Working on your first Pull Request?** You can learn how from this *free* series [How to Contribute to an Open Source Project on GitHub](https://kcd.im/pull-request)

For specific robots that are intensively used by our Research Lines (e.g., `ergoCub`), we also consider the workflow described below. 

# Easier management of `robots-configuration` on intensively used robots

## 🔲 Intro
The repository `robots-configuration` is maintained by iCub Tech and direct pushes are restricted to a few members of the facility, the rationale being that it would be very easy to mess it up otherwise. Thus, the current workflow dictates forking the repository and opening pull-requests frequently to merge changes upstream.

Having said that, for robots that are being used by many users of different research lines and with a fast development pace (e.g., `ergoCub`), it turned out that it is somewhat inconvenient to rely on the present workflow. The main drawbacks are the following:
1. To integrate changes, one developer needs to pass through a personal/organizational fork by switching the branch or copying out the relevant modifications elsewhere (e.g., on his/her system). Then, a wait state is introduced due to the PR review. Once done, it is finally required to update the local repository hosted on the robot system. Oftentimes, because this process tends to be long and cumbersome hence prone to oversights, changes are left uncommitted on the robot causing frustration among users who must deal with an untidy system.
2. The process detailed on point 1 requires that the user is logged in. However, on the robot shared system, signing in on GitHub poses some difficulties mainly due to the 2FA, which eventually curbs the leaning to make contributions upstream.

## 🔲 Fast-pace local workflow
Here's the outline of the workflow that aims to overcome/attenuate the users' headaches:
1. The organizational fork `icub-tech-iit/robots-configuration` is deployed on the robot system instead of the upstream repository `robotology/robots-configuration`.
2. We set up the machine user [`icub-tech-iit-bot`](https://github.com/icub-tech-iit-bot) on the robot system as the default committer with push access, but only locally to the repository. Push access is granted via a fine-grained PAT.
3. We enforce the use of `--author="Name Surnaname <user@email.com>"` command-line option (or the corresponding env variables) at commit time so that we can trace back who did what.
4. As a result, on the robot system, users will work and be able to push to the branch `icub-tech-iit/robots-configuration@devel` (actually, we will have robot-specific branches, see below). Some sort of push limitations will be enforced on this branch: e.g., no push force.
5. As it is paramount to enforce that at any time the configuration files allow the robot to start up flawlessly, there will be no specific automation aimed at synchronizing the upstream and the fork repositories back and forth. This process needs to be carried out under the supervision of educated humans.
    1. **Human-supervised update fork → upstream**. It is performed periodically (e.g., every fortnight) via PR's. On the fork, the deal is that users will push only fixes (e.g., calibration values) and minor modifications (changing the options of some services) to the "official" robot files. Of course, users are free to deal with RL-specific additions/amendments.
    2. **Human-supervised update upstream → fork**. It is generally performed by iCub Tech developers (who keep on working upstream) when the time comes to perform tests on the robot. Once on the robot system, the developer will be using the fork, guaranteeing that the overall robot behavior won't be negatively affected by the latest modifications. Possible fixes pushed to the fork will need to be backed up upstream via PR's.
    3. This way, there may exist the possibility that the upstream and the fork devel branches diverge generating conflicts that are discovered too late. To remedy this, an automation (i.e., a GitHub action running on the fork) will be responsible for checking the presence of conflicts between the two branches at push time. If something relevant gets detected, the push author and the upstream maintainer will be notified through an automatically generated issue so that an action can be undertaken timely.
6. To mitigate the effects of interaction among different robots, users will use robot-specific branches in the fork repository. In other words, for the `ergoCubSN???` robot, we will have, e.g., the `devel-ergoCubSN???` branch tracking the upstream devel.
7. The maintainer of `robotology/robots-configuration` will possibly apply fixes received on the devel branch also to the master branch of the upstream repository.
8. The new workflow is applied only internally to IIT and, to keep things simple, only to robot systems that are used intensively: i.e., `ergoCubSN00???`.

## 🔲 [Technicalities](./local-workflow-tech.md)
