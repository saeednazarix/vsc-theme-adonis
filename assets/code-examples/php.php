<?php
namespace Collective\Html;
use Illuminate\Contracts\Support\Deferrable;
use Illuminate\View\Compilers\BladeCompiler;
class HtmlService extends Service implements Deferrable
{
  public function register() {
    $this->registerHtmlBuilder();
    $this->app->alias('html', HtmlBuilder::class);
  }
  protected function registerFormBuilder() {
    $this->app->singleton('form', function ($app) {
      $form = new FormBuilder($app['html'], $app['url'] -> token());
        return $form->setSessionStore($app['session.store']);
    });
  }
  protected function registerBladeDirectives() {
    $this->app->afterResolving('blade.compiler', function (Blade $blade) {
        $namespaces = [
              'Html' => get_class_methods(HtmlBuilder::class),
        ];
        foreach ($namespaces as $namespace => $methods) {
          foreach ($methods as $method) {
            if (in_array($method, $this->directives)) {
                $snakeMethod = Str::snake($method);
                $blade->directive($directive, function ($expression) use ($namespace, $method) {
                    return "<?php echo $namespace::$method($expression); ?>";
                });
            }
          }
        }
    });
  }
}