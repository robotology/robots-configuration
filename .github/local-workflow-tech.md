Technicalities underlying the fast-pace local workflow
======================================================

## 🔲 Set up the options of the fork repository
- Create a ruleset that:
  - Targets all branches.
  - Restricts updates.
  - Restricts deletions.
  - Blocks force pushes.
- Disable the option `Automatically delete head branches`.

## 🔲 Clone the fork locally
- Clone the `icub-tech-iit` fork:
  ```console
  git remote add icub-tech https://github.com/icub-tech-iit/robots-configuration.git
  ```
- Switch to the branch corresponding to the robot (e.g., `devel-ergoCubSN???`).

## 🔲 Set the default committer
- In order to push to the `icub-tech` fork without password, it is necessary to get a PAT from the maintainer. Then, issue the following commands:
  ```console
  git config --local user.name "icub-tech-iit-bot"
  git config --local user.email "icub-tech@iit.it"
  PAT=<insert the PAT here>
  git remote set-url icub-tech https://x-access-token:${PAT}@github.com/icub-tech-iit/robots-configuration.git
  ```
  ⚠️ Note the use of the option `--local` to avoid impacting Git globally on the system.
- The PAT is set to have no expiration. However, it can be revoked at any time by the maintainer.

## 🔲 Ensure that the author information is specified explicitly at commit time
- We do rely on [Git hoooks](../.githooks).
- Run the following command from the `robots-configuration` root folder:
  ```console
  git config --local core.hooksPath .githooks/
  ```

# 🔘 Use an external robots-configuration separately from `robotology-superbuild`

In some `ergoCubSN???` setups, the `robots-configuration` used by the robot is not the one downloaded by the `robotology-superbuild` (that would be found at `/usr/local/src/robot/robotology-superbuild/src/robots-configuration`),
but rather a separate `robots-configuration` available at `/usr/local/src/robot/robots-configuration`. This is done for two reasons:
- To permit to clone a fresh new `robotology-superbuild`, without the need to manually perform the local repository configuration as described in the previous section,
- To permit to easily share the used `robots-configuration` to other `robotology-superbuild`, that for example are part of a different environment or a different container.

The steps necessary to switch to use an external robots-configuration given an existing `robotology-superbuild` setup are the following:

## 🔲 Disable robots-configuration from the superbuild

First of all, pass the [`-ROBOTOLOGY_SKIP_ROBOTS_CONFIGURATION:BOOL=ON`](https://github.com/robotology/robotology-superbuild/pull/1775) CMake option to all the `robotology-superbuild` that should use the external `robots-configuration`.

If the `robotology-superbuild` was already built once, remember to first uninstall and then delete the existing robots-configuration repository to avoid confusion.

In particular uninstall with:

```console
cd /usr/local/src/robot/robotology-superbuild/build/src/robots-configuration
make uninstall
```

and delete any `robots-configuration` folder with:

```console
cd /usr/local/src/robot/robotology-superbuild
rm -rf /usr/local/src/robot/robotology-superbuild/src/robots-configuration
rm -rf /usr/local/src/robot/robotology-superbuild/build/src/robots-configuration
```

## 🔲 Clone, install and ensure that external robots-configuration is visible

```console
cd /usr/local/src/robot
git clone  https://github.com/robots-configuration/robots-configuration.git
cd robots-configuration
```

At this point, follow the configuration steps documented in the earlier section. Then, install the repo without dependencies, using the `nodeps` CMake preset:

```console
cmake --preset nodeps
cmake --install build
```

After you did all of this, to ensure that the installed files are found by YARP, add the following line to the `.bashrc_iCub` of the robot:

```console
export YARP_DATA_DIRS=$YARP_DATA_DIRS:/usr/local/src/robot/robots-configuration/build/install/share/ICUBcontrib
```
