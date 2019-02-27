angular.module('volunteersTable', ['angular-table']).controller('volunteerController', ['$scope', '$window', '$filter', function ($scope, $window, $filter) {
  $scope.volunteers = [{label: 'Henter'}];

  /** redo this **/
  function load() {
    $scope.volunteers = $window.valghalla_volunteers;

    // $scope.$apply();
    $scope.$evalAsync();
  }

  jQuery(document).on('volunteersLoaded', function () {
    load();
  });

  $scope.config = {
    itemsPerPage: 10,
    fillLastPage: true
  };

  $scope.reset = function () {
    $scope.query = '';

    load();
  };

  $scope.updateFilteredList = function () {
    $scope.volunteers = $filter("filter")($window.valghalla_volunteers, $scope.query);
  };
}]);
