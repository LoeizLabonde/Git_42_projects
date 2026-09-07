<?php
// Minimal wp-config.php that reads DB credentials from environment variables.
// This avoids baking secrets into the image and lets Compose pass the values at runtime.

define('DB_NAME', getenv('WORDPRESS_DB_NAME') ? getenv('WORDPRESS_DB_NAME') : getenv('MYSQL_DATABASE'));
define('DB_USER', getenv('WORDPRESS_DB_USER') ? getenv('WORDPRESS_DB_USER') : getenv('MYSQL_USER'));
define('DB_PASSWORD', getenv('WORDPRESS_DB_PASSWORD') ? getenv('WORDPRESS_DB_PASSWORD') : getenv('MYSQL_PASSWORD'));
define('DB_HOST', getenv('WORDPRESS_DB_HOST') ? getenv('WORDPRESS_DB_HOST') : 'localhost');

define('DB_CHARSET', 'utf8');
define('DB_COLLATE', '');

// Force WordPress to use the correct URL (only if not already defined by wp-cli)
if (!defined('WP_HOME')) {
    define('WP_HOME', 'https://localhost');
}
if (!defined('WP_SITEURL')) {
    define('WP_SITEURL', 'https://localhost');
}

// Authentication Unique Keys and Salts.
// For development we use simple placeholders; rotate for production.
define('AUTH_KEY',         'put your unique phrase here');
define('SECURE_AUTH_KEY',  'put your unique phrase here');
define('LOGGED_IN_KEY',    'put your unique phrase here');
define('NONCE_KEY',        'put your unique phrase here');
define('AUTH_SALT',        'put your unique phrase here');
define('SECURE_AUTH_SALT', 'put your unique phrase here');
define('LOGGED_IN_SALT',   'put your unique phrase here');
define('NONCE_SALT',       'put your unique phrase here');

$table_prefix = 'wp_';

// Enable debugging during development. Do not enable in production.
define('WP_DEBUG', true);
// Log debug messages to `wp-content/debug.log` (file will be created if needed).
define('WP_DEBUG_LOG', true);
// Display errors during development so we can diagnose DB connection issues.
define('WP_DEBUG_DISPLAY', true);
@ini_set('display_errors', 1);

if ( !defined('ABSPATH') )
    define('ABSPATH', __DIR__ . '/');

require_once(ABSPATH . 'wp-settings.php');
