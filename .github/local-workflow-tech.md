Technicalities underlying the fast-pace local workflow
======================================================

## 🔲 Set the default committer
- Fine-grained PAT can be scoped to work on a specified organization and only on a specified repository.
- To store credentials locally, one needs to issue the following, once the fork is cloned locally:
  ```console
  git config --local user.name "icub-tech-iit-bot"
  git config --local user.email "icub-tech@iit.it"
  git config --local credential.helper store
  ```
  ⚠️ Note the use of the option `--local` to avoid impacting Git globally on the system.
- The first time there's a push, the PAT needs to be provided. The credentials will be stored plainly under `~/.git-credentials` (the format is: `https://icub-tech-iit-bot:<PAT>`). No worries though, as this PAT has a very narrowed use and impacts a fork that is backed up anyhow by the upstream repository. The PAT can be stored in `~/.git-credentials` upfront as well. Being the local system shared, no one else should store his/her PAT in the same file.
- ⌛ The PAT expires after **`1 year`** at the latest, thus needing to be regenerated.
- The upstream maintainer will take care of the PAT.

## 🔲 Ensure that the author information is specified explicitly at commit time
- We do rely on [Git hoooks](../.githooks).
- After cloning the fork locally, issue:
  ```console
  git config --local core.hooksPath .githooks/
  ```

## 🔲 Detect conflicts at push time and notify PIC

> [!note]
> To be still developed.
