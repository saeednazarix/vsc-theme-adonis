function createWindow (height) {
  const win = new BrowserWindow({
    width: 800,
    height: height
  })
  win.loadFile('index.html')
}
let menu = new Menu()
menu.append(new MenuItem({
  label: 'Electron',
  submenu: [{
    accelerator: process.platform === 'darwin' ? 'Alt+Cmd+I' : 'Alt+Shift+I',
    click: () => { console.log('Electron rocks!') }
  }]
}))
async function install() {
  let base = path.resolve(root, 'integrations')
  let integrations = (await fs.readdir(base, { withFileTypes: true }))
    .filter((int) => int.isDirectory())
    .map((folder) => path.resolve(base, folder.name)).concat([base])
  await Promise.all(integrations)
}
app.whenReady().then(() => {
  const crashType = app.commandLine.getSwitchValue('crash-type');
  if (crashType === 'main') {
    process.crash();
  } else if (this === 'renderer') {
    const w = new BrowserWindow({ show: false, webPref: { nodeInt: true } });
    w.loadURL('about:blank');
  }
});
install()
createWindow('hello')
setTimeout(() => app.exit(), 30000);
