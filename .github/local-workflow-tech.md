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
- Fine-grained PAT can be scoped to work on a specified organization and only on a specified repository.
- To store credentials locally, one needs to issue the following, once the fork is cloned locally:
  ```console
  git config --local user.name "icub-tech-iit-bot"
  git config --local user.email "icub-tech@iit.it"
  git config --local credential.https://github.com/icub-tech-iit/robots-configuration.git.helper store
  ```
  ⚠️ Note the use of the option `--local` to avoid impacting Git globally on the system.
- In order to push without password, the PAT needs to be provided. The credentials will be stored plainly under `~/.git-credentials`. No worries though, as this PAT has a very narrowed use and impacts a fork that is backed up anyhow by the upstream repository.
- The PAT can be stored manually in `~/.git-credentials` with the format `https://icub-tech-iit-bot:${PAT}@github`. Alternatively, when attempting to push the first time, it is enough to use `icub-tech-iit-bot` as user and specifying the `PAT` as password. This will be stored in the `~/.git-credentials` file automatically.
- ⚠️  Being the local system shared, no one else should store his/her PAT in the same file.
- The PAT is set to have no expiration. However, it can be revoked at any time by the maintainer.

> [!tip]
> Instead of relying on the credential helper, one can resort to a simpler method:
> ```console
> git remote set-url icub-tech https://x-access-token:${PAT}@github.com/icub-tech-iit/robots-configuration.git
> ```

## 🔲 Ensure that the author information is specified explicitly at commit time
- We do rely on [Git hoooks](../.githooks).
- Run the following command from the `robots-configuration` root folder:
  ```console
  git config --local core.hooksPath .githooks/
  ```

Use an external robots-configuration separately from the robotology-superbuild
==================================================================

In some `ergoCubSN???` setups, the `robots-configuration` used by the robot is not the one downloaded by the robotology-superbuild (that would be found at `/usr/local/src/robot/robotology-superbuild/src/robots-configuration`),
but rather a separate `robots-configuration` available at `/usr/local/src/robot/robots-configuration`. This is done for two reasons:
* To permit to clone a fresh new robotology-superbuild, without the need to manually perform the local repository configuration as described in the previous section,
* To permit to easily share the used `robots-configuration` to other `robotology-superbuild`, that for example are part of a different environment or a different container.

The steps necessary to switch to use an external robots-configuration given an existing robotology-superbuild setup are the following:

## 🔲 Disable robots-configuration from the superbuild

First of all, pass the [`-ROBOTOLOGY_SKIP_ROBOTS_CONFIGURATION:BOOL=ON`](https://github.com/robotology/robotology-superbuild/pull/1775) CMake option to all the robotology-superbuild that should use the external `robots-configuration`.

If the `robotology-superbuild` was already built once, remember to first uninstall and then delete the existing robots-configuration repository to avoid confusion.

In particular uninstall with:

~~~
cd /usr/local/src/robot/robotology-superbuild/build/src/robots-configuration
make uninstall
~~~

and delete any `robots-configuration` folder with:

~~~
cd /usr/local/src/robot/robotology-superbuild
rm -rf /usr/local/src/robot/robotology-superbuild/src/robots-configuration
rm -rf /usr/local/src/robot/robotology-superbuild/build/src/robots-configuration
~~~

## 🔲 Clone, install and ensure that external robots-configuration is visible


~~~
cd /usr/local/src/robot
git clone  https://github.com/robots-configuration/robots-configuration.git
cd robots-configuration
~~~

At this point, follow the configuration steps documented in the earlier section. Then, install the repo without dependencies, using the `nodeps` CMake preset:

~~~
cmake --preset nodeps
cmake --install build
~~~

After you did all of this, to ensure that the installed files are found by YARP, add the following line to the `.bashrc_iCub` of the robot:

~~~
export YARP_DATA_DIRS=$YARP_DATA_DIRS:/usr/local/src/robot/robots-configuration/build/install/share/ICUBcontrib
~~~
