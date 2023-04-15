pub trait ModChar {
    fn is_ascii_underscore_or_dollarsign(&self) -> bool;
    fn is_ascii_alnum_or_underscoredollar(&self) -> bool;
    fn is_ascii_dble_sngl_bk(&self) -> bool;
}

impl ModChar for u8 {
    fn is_ascii_underscore_or_dollarsign(&self) -> bool {
        *self == 95 || *self == 36
    }

    fn is_ascii_alnum_or_underscoredollar(&self) -> bool {
        self.is_ascii_alphanumeric() || self.is_ascii_underscore_or_dollarsign()
    }

    fn is_ascii_dble_sngl_bk(&self) -> bool {
        // double, single or back quotues/ticks
        *self == 34 || *self == 39 || *self == 96
    }
}
