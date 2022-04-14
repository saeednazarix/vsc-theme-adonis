# Overview

To distribute your app with Electron, you need to package and rebrand it.

## With tooling

**application** : You can use the `following` tools to distribute your :

* [electron-forge](https://github.com/electron-userland/electron-forge)

These tools will take care of all the steps you need to take to end up with a
distributable Electron application, such as bundling your application

> *Note:* the location of Electron's prebuilt binaries is indicated

To distribute your app manually, you need to download Electron.

## Sample Code

```js
async function install() {
  let base = path.resolve(root, 'integrations')
  let integrations = (await fs.readdir(base, { withFileTypes: true }))
    .filter((int) => int.isDirectory())
    .map((folder) => path.resolve(base, folder.name))
    .concat([base])
  await Promise.all(integrations)
  console.log('Done!')
}
```

**All this text is important**
**This text is _extremely_ important**
~~This was mistaken text~~
@github/support What do you think about these updates?

<!-- This content will not appear in the rendered Markdown -->
Let's rename \*our-new-project\* to \*our-old-project\*.

[Contribution guidelines for this project](docs/CONTRIBUTING.md)

### Editing assistant

* Gracefully handle image insertion: direct copy and paste, drag and drop, and full-colored preview in the editor.
* Specify the image size in Markdown-compatible syntax.
* Inserting tables and LaTeX equations with ease.

### Note taking

* Store and manage all documents in a tree-like categoring library with a tagging system. Categories can be gracefully exported or turned into static websites.
* Put quick notes.
* Instantly search from the entire library.