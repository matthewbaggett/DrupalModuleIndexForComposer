<?php

class Package{
    public $name;
    public $version;
    public $version_normalised;
    public $dist = array();
    public $require = array();
    public $type = 'drupal-module';

    public function __construct(){
        $this->require['type'] = 'tar';
        $this->require['url'] = null;
        $this->require['reference'] = null;
        $this->require['shasum'] = null;
    }
}