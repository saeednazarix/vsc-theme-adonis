use std::collections::HashSet;

fn main() {
    let set_a = HashSet::from([0, 1]);
    let set_b = HashSet::from([2, 3]);
    let set_c: HashSet<_> = set_a.union(&set_b).collect();
    dbg!(set_c);
    let set_d: HashSet<_> = [set_a, set_b]
        .into_iter()
        .reduce(|acc, set| acc.union(&set).cloned().collect())
        .unwrap();
    dbg!(set_d);
}

#[macro_export]
macro_rules! vec {
    ( $( $x:expr ),* ) => {
        {
            let mut temp_vec = Vec::new();
            $(
                temp_vec.push($x);
            )*
            temp_vec
        }
    };
}
use hello_macro::HelloMacro;
struct Pancakes;
impl HelloMacro for Pancakes {
    fn hello_macro() {
        println!("Hello, Macro! My name is Pancakes!");
    }
}
fn main() {
    Pancakes::hello_macro();
}
let mut h = highlight_def(db, def);

if let Definition::Local(local) = &def {
    if is_consumed_lvalue(name_ref.syntax().clone().into(), local, db) {
        h |= HighlightModifier::Consuming;
    }
}

if let Some(parent) = name_ref.syntax().parent() {
    if matches!(parent.kind(), FIELD_EXPR | RECORD_PAT_FIELD) {
        if let Definition::Field(field) = def {
            if let VariantDef::Union(_) = field.parent_def(db) {
                h |= HighlightModifier::Unsafe;
            }
        }
    }
}